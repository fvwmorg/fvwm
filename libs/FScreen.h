/* -*-c-*- */
#ifndef FVWMLIB_FSCRREN_H
#define FVWMLIB_FSCRREN_H

/* needs X11/Xlib.h and X11/Xutil.h */
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef FVWMLIB_FSCRREN_H
#define FVWMLIB_FSCRREN_H

/* ---------------------------- included header files ---------------------- */

/* Do not #include any files - the file including this file has to take care of
 * it.  Make sure all necessary headers are listed in the Synopsis section. */

/* ---------------------------- global definitions ------------------------- */

#define FSCREEN_MANGLE_USPOS_HINTS_MAGIC ((short)-32109)

/* ---------------------------- global macros ------------------------------ */

/* ---------------------------- type definitions --------------------------- */

typedef struct DesktopsInfo
{
	int desk;
	char *name;

	struct
	{
		int x;
		int y;
		int width;
		int height;
	} ewmh_working_area;
	struct
	{
		int x;
		int y;
		int width;
		int height;
	} ewmh_dyn_working_area;

	struct DesktopsInfo *next;
} DesktopsInfo;

typedef union
{
	XEvent *mouse_ev;
	const char *name;
	struct
	{
		int x;
		int y;
	} xypos;
} fscreen_scr_arg;

typedef enum
{
	FSCREEN_GLOBAL  = -1,
	FSCREEN_CURRENT = -2,
	FSCREEN_PRIMARY = -3,
	FSCREEN_XYPOS   = -4
} fscreen_scr_t;

typedef enum
{
	FSCREEN_SPEC_GLOBAL = 'g',
	FSCREEN_SPEC_CURRENT = 'c',
	FSCREEN_SPEC_PRIMARY = 'p',
	FSCREEN_SPEC_WINDOW = 'w'
} fscreen_scr_spec_t;

typedef union
{
	XEvent *mouse_ev;
	struct
	{
		int x;
		int y;
	} xypos;
} fscreen_scr_arg;

/* Control */
Bool FScreenIsEnabled(void);
Bool FScreenIsSLSEnabled(void);
void FScreenInit(Display *dpy);
void FScreenOnOff(Bool do_enable);
Bool FScreenConfigureSLSSize(int width, int height);
Bool FScreenConfigureSLSScreens(int nscreens, char *args);
void FScreenSLSOnOff(Bool do_enable);
/* Intended to be called by modules.  Simply pass in the parameter from the
 * config string sent by fvwm. */
void FScreenConfigureModule(char *args);
const char* FScreenGetConfiguration(void); /* For use by fvwm */
void FScreenSetDefaultModuleScreen(char *scr_spec);
void FScreenDisableRandR(void);

void FScreenSetPrimaryScreen(int scr);

/* Screen info */
Bool FScreenGetScrRect(
	fscreen_scr_arg *arg, fscreen_scr_t screen, int *x, int *y,
	int *w, int *h);
Bool FScreenGetScrId(
	fscreen_scr_arg *arg, fscreen_scr_t screen);
void FScreenTranslateCoordinates(
	fscreen_scr_arg *arg_src, fscreen_scr_t screen_src,
	fscreen_scr_arg *arg_dest, fscreen_scr_t screen_dest,
	int *x, int *y);
void FScreenGetResistanceRect(
	int wx, int wy, unsigned int ww, unsigned int wh, int *x0, int *y0,
	int *x1, int *y1);
Bool FScreenIsRectangleOnScreen(
	fscreen_scr_arg *arg, fscreen_scr_t screen, rectangle *rec);
void FScreenSpecToString(char *dest, int space, fscreen_scr_t screen);
int FScreenOfPointerXY(int x, int y);


/* Clipping/positioning */
int FScreenClipToScreen(
	fscreen_scr_arg *arg, fscreen_scr_t screen, int *x, int *y, int w,
	int h);
void FScreenCenterOnScreen(
	fscreen_scr_arg *arg, fscreen_scr_t screen, int *x, int *y, int w,
	int h);

/* Geometry management */
int FScreenGetScreenArgument(char *scr_spec, fscreen_scr_spec_t default_screen);
int FScreenParseGeometryWithScreen(
	char *parsestring, int *x_return, int *y_return,
	unsigned int *width_return, unsigned int *height_return,
	int *screen_return);
int FScreenParseGeometry(
	char *parsestring, int *x_return, int *y_return,
	unsigned int *width_return, unsigned int *height_return);
int  FScreenGetGeometry(
	char *parsestring, int *x_return, int *y_return,
	int *width_return, int *height_return, XSizeHints *hints, int flags);
void FScreenMangleScreenIntoUSPosHints(fscreen_scr_t screen, XSizeHints *hints);
fscreen_scr_t FScreenFetchMangledScreenFromUSPosHints(XSizeHints *hints);

/* RandR support */
int  FScreenGetRandrEventType(void);
Bool FScreenHandleRandrEvent(
	XEvent *event, int *old_w, int *old_h, int *new_w, int *new_h);

#endif /* FVWMLIB_FSCRREN_H */
