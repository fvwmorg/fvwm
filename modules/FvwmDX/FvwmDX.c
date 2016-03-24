/*
 * FvwmDx, Copyright 2016
 *
 */

/* This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see: <http://www.gnu.org/licenses/>
 */

#include "config.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "libs/Module.h"
#include "libs/Parse.h"
#include "libs/fvwmlib.h"
#include "libs/FScreen.h"
#include "fvwm/fvwm.h"
#include "libs/vpacket.h"
#include "libs/safemalloc.h"

//#define DEBUG 1

#define FVWMDX_DX	"*FvwmDXScreens"

#define MAX_SCREENS	64			/* Yay, arbitrary limits. */

#if DEBUG
#define SendText(fvwm,cmd,wid) ({ \
	fprintf(stderr, "Command [%08lx]: %s\n", (unsigned long)(wid), cmd); \
	SendText(fvwm,cmd,wid); })
#endif

static Display *dpy;
static int fvwm[2];
static char *prog = NULL;

/* The desktop the windows are supposed to be a member of, even though
   they aren't. */
static int screen_conf[MAX_SCREENS];
static int screens;

typedef struct {
	int x, y, w, h;
} wsize_t;
static wsize_t screen_size[MAX_SCREENS];

/**/

typedef struct list list_t;
struct list {
	list_t *next;
	unsigned long w;
	enum {
		SWITCHER_MADE_HIDDEN,
		SWITCHER_MADE_STICKY,
		SWITCHER_NEED_SWAP
	} style;
	int desk; /* for hidden/swap */
};

#define LIST_STEP	1024
static list_t free_list = { NULL };

static void alloc_list(void)
{
	int i;
	list_t *ents = (void*)safemalloc(sizeof(*ents) * LIST_STEP);
	for (i = 0; i < (LIST_STEP-1); i++)
		ents[i].next = &ents[i+1];
	ents[i].next = NULL;
	free_list.next = &ents[0];
}

static list_t *list_alloc(void)
{
	list_t *ret;
	if (!free_list.next) { alloc_list(); }
	ret = free_list.next;
	free_list.next = ret->next;
	return ret;
}

#define list_insert(pos,node) ( (node)->next = (pos)->next, (pos)->next = (node) )
#define list_free_node(node) (list_insert(&free_list, (node)))

/**/

static void SendTextVA(unsigned long wid, char *fmt, ...)
{
	va_list argp;
	char command[1024];

	va_start(argp, fmt);
	vsnprintf(command, sizeof(command), fmt, argp);
	va_end(argp);

	SendText(fvwm, command, wid);
}

static void parse_screen_config(char *line)
{
	int i;
	int scan_screens;

	scan_screens = GetIntegerArguments(
		line + sizeof(FVWMDX_DX) + 1, /* hack */
		NULL,
		screen_conf,
		MAX_SCREENS
	);

	for (i = scan_screens; i < screens; i++)
		screen_conf[i] = screen_conf[0];
}

static void get_screen_config(void)
{
	char *line;

	InitGetConfigLine(fvwm, FVWMDX_DX);
	while (GetConfigLine(fvwm, &line), line != NULL) {
		if (strncasecmp(line, FVWMDX_DX, sizeof(FVWMDX_DX) - 1))
			continue;

		parse_screen_config(line);
	}
}

static void swap_windows(int from_desk, int to_desk, int swap_all);
static void sync_screen_config(int current_desk)
{
	if (screen_conf[0] != current_desk)
		swap_windows(screen_conf[0], current_desk, 1);
}

static void get_screens(void)
{
	int i;
	int real_screens;

	for (i = 1; i < MAX_SCREENS; i++) {
		if (!FScreenGetScrRect(
			NULL, i - 1,
			&screen_size[i].x,
			&screen_size[i].y,
			&screen_size[i].w,
			&screen_size[i].h
		)) {
			/* FScreen refuses to have a function that gives us
			   the total number of screens.  Great. */
			break;
		}
	}

	real_screens = i;
	for (i = screens; i < real_screens; i++)
		screen_conf[i] = screen_conf[0];
	screens = real_screens;
}


static void set_screen_config(void)
{
	int i;
	int write_screens;

	char command[2048];
	int pos;

	for (i = screens - 1; i > 0; i--) {
		if (screen_conf[i] != screen_conf[0]) break;
	}
	write_screens = i + 1;

	SendTextVA(0, "DestroyModuleConfig %s", &FVWMDX_DX[1]);

	snprintf(command, sizeof(command), FVWMDX_DX);
	pos = strlen(command);
	for (i = 0; i < write_screens; i++) {
		snprintf(&command[pos], sizeof(command) - pos, " %d", screen_conf[i]);
		pos += strlen(&command[pos]);
	}

	SendText(fvwm, command, 0);
}

static int screen_for_window(ConfigWinPacket *p)
{
	int i;
	int largest_size = 0;
	int largest_screen = 0;
	int x0, y0, x1, y1;

	for (i = 1; i < screens; i++) {
		int size;
		x0 = p->frame_x;
		y0 = p->frame_y;
		x1 = p->frame_x + p->frame_width - 1;
		y1 = p->frame_y + p->frame_height - 1;

		if (x0 < screen_size[i].x) x0 = screen_size[i].x;
		if (y0 < screen_size[i].y) y0 = screen_size[i].y;
		if (x1 >= (screen_size[i].x+screen_size[i].w))
			x1 = (screen_size[i].x+screen_size[i].w)-1;
		if (y1 >= (screen_size[i].y+screen_size[i].h))
			y1 = (screen_size[i].y+screen_size[i].h)-1;

		if (x1 <= x0 || y1 <= y0)
			continue;

		size = (x1 - x0)*(y1 - y0);
		if (size > largest_size) {
			largest_size = size;
			largest_screen = i;
		}
	}

	return largest_screen;
}

static void move_to_desk(unsigned long wid, int desk)
{
	SendTextVA(wid, "MoveToDesk 0 %d", desk);
}

static void make_sticky_desk(unsigned long wid, int sticky)
{
	SendTextVA(wid, "StickAcrossDesks %s", sticky ? "true" : "false");
}

static void goto_desk(int desk)
{
	SendTextVA(0, "GotoDesk 0 %d", desk);
}

static unsigned long get_desk(void)
{
	FvwmPacket *packet;
	int from_desk;

	/* Try to get just the current desktop number.. */
	SendText(fvwm, "Send_WindowList Desk NoDeskNum", 0);
	while ((packet = ReadFvwmPacket(fvwm[1])) != NULL && packet->type != M_END_WINDOWLIST) {
		if (packet->type != M_NEW_DESK) continue;

		from_desk = packet->body[0];

		while ((packet = ReadFvwmPacket(fvwm[1])) != NULL && packet->type != M_END_WINDOWLIST)
			;

		return from_desk;
	}

	return 0;
}

/*
current screen;
	if the fake desktop is the destination desktop:
		hide all windows on the destination [dest: real]
		stick all windows on the real
		do stick/hide for other screens
		switch desktop
		move all hidden windows
		unstick all windows
		fake = real = destination desktop
	if the real desktop is the destination desktop:
		do nothing! at all!
	otherwise:
		do stick/hide for other screens
		switch desktop
		if fake != real:
			swap all fake/real windows
		move all hidden windows
		unstick all windows
		fake = real = destination desktop

other screens (UNswitched);
	if the real desktop is the destination desktop:
		... again, nothing.
	otherwise:
		hide all windows on the destination [dest: fake]
		stick all windows on the real
		switch desktop
		if fake != real and fake != destination:
			swap all fake/real windows
		fake = previous value
		real = destination desktop
*/
static void swap_windows(int from_desk, int to_desk, int swap_all)
{
	FvwmPacket *packet;
	int hide_desk = -1;
	int screen;

	list_t winlist;
	list_t *node, *next;

	hide_desk = 0;
	while (hide_desk == from_desk || hide_desk == to_desk)
		++hide_desk;

#if DEBUG
	fprintf(stderr, "swap_windows: [%d]%d %d %d\n",
		screen_conf[0],
		from_desk,
		to_desk,
		swap_all
	);
#endif

	winlist.next = NULL;

	screen = FScreenGetScrId(NULL, FSCREEN_CURRENT);
	if (screen <= 0) screen = FScreenGetScrId(NULL, FSCREEN_PRIMARY);
	if (screen <= 0) {
		fprintf(stderr, "%s: Unable to obtain current screen.\n", prog);
		return;
	}

	SendText(fvwm, "Send_WindowList NoStickyDesk", 0);
	while ((packet = ReadFvwmPacket(fvwm[1])) != NULL && packet->type != M_END_WINDOWLIST) {
		ConfigWinPacket *p;
		int w_screen;

		if (packet->type != M_CONFIGURE_WINDOW) continue;

		p = (ConfigWinPacket*)packet->body;

#if DEBUG
		fprintf(stderr, "CONFIGURE_WINDOW %08lx\n", p->w);
#endif

		node = NULL;

		w_screen = screen_for_window(p);

		if (!w_screen)
			continue;

		/* Unfortunately, fvwm manages to give us sticky windows
		   even if we requested none.  Excellent. */
		/* Even better: It won't give us _NON_ sticky windows if we've
		   set them sticky before. */
		if (IS_STICKY_ACROSS_DESKS(p)) {
#if DEBUG
			fprintf(stderr, "ignored %08lx due to StickyDesk status\n", p->w);
#endif
			continue;
		}

		if (w_screen != screen && !swap_all) {
			if (p->desk == to_desk && from_desk == to_desk && screen_conf[w_screen] == to_desk) {
				/* Nothing */
			} else if (p->desk == to_desk) {
				/* Hide; switch to real if (fake != real && fake != destination) */
				/* fake otherwise */
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_MADE_HIDDEN;
				if (screen_conf[w_screen] != from_desk && screen_conf[w_screen] != to_desk)
					node->desk = screen_conf[w_screen];
				else
					node->desk = from_desk;
				list_insert(&winlist, node);
			} else if (p->desk == from_desk) {
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_MADE_STICKY;
				list_insert(&winlist, node);
			} else if (p->desk == screen_conf[w_screen]) {
				/* fake(screen_conf[w_screen]) != real(from_desk) */
				/* fake(screen_conf[w_screen]) != destination(to_desk) */
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_NEED_SWAP;
				node->desk = from_desk;
				list_insert(&winlist, node);
			}
		} else if (screen_conf[w_screen] == to_desk) {
			if (p->desk == to_desk && from_desk == to_desk) {
				/* Nothing */
			} else if (p->desk == to_desk) {
				/* Hide; switch to real */
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_MADE_HIDDEN;
				node->desk = from_desk;
				list_insert(&winlist, node);
			} else if (p->desk == from_desk) {
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_MADE_STICKY;
				list_insert(&winlist, node);
			}
		} else if (screen_conf[w_screen] != from_desk) {
			/* Swap fake/real */
			if (p->desk == from_desk) {
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_NEED_SWAP;
				node->desk = screen_conf[w_screen];
				list_insert(&winlist, node);
			} else if (p->desk == screen_conf[w_screen]) {
				node = list_alloc();
				node->w = p->w;
				node->style = SWITCHER_NEED_SWAP;
				node->desk = from_desk;
				list_insert(&winlist, node);
			}
		}

		/* ... actually make it hidden/sticky */
		if (node) switch (node->style) {
		  case SWITCHER_MADE_HIDDEN:
			/* :E Best way I could think of to "hide" it... */
			move_to_desk(node->w, hide_desk);
			break;
		  case SWITCHER_MADE_STICKY:
			make_sticky_desk(node->w, 1);
			break;
		  case SWITCHER_NEED_SWAP:
			/* nothing */
			break;
		  default:
			break;
		}
	}

	goto_desk(to_desk);

	for (node = winlist.next; node; node = next) {
		switch (node->style) {
		  case SWITCHER_MADE_HIDDEN:
		  case SWITCHER_NEED_SWAP:
			move_to_desk(node->w, node->desk);
			break;
		  case SWITCHER_MADE_STICKY:
			make_sticky_desk(node->w, 0);
			break;
		}
		next = node->next;
		list_free_node(node);
	}

	if (swap_all) {
		int i;
		for (i = 0; i < screens; i++)
			screen_conf[i] = to_desk;
	} else {
		screen_conf[0] = to_desk;
		screen_conf[screen] = to_desk;
	}

	set_screen_config();
}

static void CMD_GotoDesk(char *args)
{
	char *next, *token;
	int swap_all;
	int narg;
	int arg[4];
	int to_desk;
	int screen;

	token = PeekToken(args, &next);
	if (!strcasecmp(token, "*")) {
		args = next;
		swap_all = 1;
	} else {
		swap_all = 0;
	}

	narg = GetIntegerArguments(args, &next, arg, 4);
	if (arg <= 0)
		return;

	to_desk = arg[0];
	if (!to_desk && narg >= 2)
		to_desk = arg[1];
	if (narg >= 4) {
		if (to_desk < arg[2]) to_desk = arg[2];
		if (to_desk > arg[3]) to_desk = arg[3];
	}

	screen = FScreenGetScrId(NULL, FSCREEN_CURRENT);

	if (screen_conf[screen] != to_desk || swap_all)
		swap_windows(screen_conf[0], to_desk, swap_all);
}

static void CMD_Quit(char *args)
{
	FvwmPacket *packet;

	swap_windows(screen_conf[0], screen_conf[0], 1);

	SendText(fvwm, "Send_ConfigInfo Nothing.", 0);
	while ((packet = ReadFvwmPacket(fvwm[1])) != NULL) {
		if (packet->type == M_END_CONFIG_INFO)
			break;
	}
	exit(0);
}

static void ParseCommand(FvwmPacket *packet)
{
	char *cmd = (char*)&packet->body[3];
	char *args, *token;

	token = PeekToken(cmd, &args);
#if DEBUG
	fprintf(stderr, "PacketCommand[%s]: %s\n", token, cmd);
#endif
	if (token) {
		if (!strcasecmp(token, "GotoDesk")) {
			CMD_GotoDesk(args);
		} else if (!strcasecmp(token, "Quit")) {
			CMD_Quit(args);
		} else if (!strcasecmp(token, FVWMDX_DX)) {
			int desk = screen_conf[0];
			parse_screen_config(cmd);
			sync_screen_config(desk);
		}
	}
}

int main(int argc, char *argv[])
{
	FvwmPacket *packet;

#if 0
	stderr = fopen("/tmp/fvwmdx.log", "w");
	setbuffer(stderr, NULL, 0);
#endif

	prog = strrchr(argv[0], '/');
	if (prog) ++prog; else prog = argv[0];

	if (argc < (1+5)) {
		fprintf(stderr, "%s: Module %s\n", prog, argv[0]);
		return -1;
	}

	fvwm[0] = atoi(argv[1]);
	fvwm[1] = atoi(argv[2]);

	dpy = XOpenDisplay(NULL);
	if (!dpy) {
		fprintf(stderr, "Display error.\n");
		return -1;
	}

	FScreenInit(dpy);

	SetMessageMask(
		fvwm,
		M_CONFIGURE_WINDOW | M_END_WINDOWLIST |
		M_CONFIG_INFO | M_END_CONFIG_INFO |
		M_NEW_DESK |
		M_STRING
	);

	get_screens();
	get_screen_config();
	sync_screen_config(get_desk());

	SendText(fvwm, "NOP FINISHED STARTUP", 0);

#if DEBUG
	fprintf(stderr, "Initialized.\n");
#endif

	while ((packet = ReadFvwmPacket(fvwm[1])) != NULL) {
#if DEBUG
		fprintf(stderr, "Packet type %lu\n", packet->type);
#endif
		switch (packet->type) {
		  case M_STRING:
			ParseCommand(packet);
			break;
		  case M_NEW_DESK:
			sync_screen_config(packet->body[0]);
			break;
		}
	}

	return 0;
}
