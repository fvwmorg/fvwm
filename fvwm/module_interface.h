/* -*-c-*- */

#ifndef FVWM_MODULE_INTERFACE_H
#define FVWM_MODULE_INTERFACE_H

#include "Module.h"
#include "libs/queue.h"

/* please don't use msg_masks_t and PipeMask outside of module_interface.c.
 * They are only global to allow to access the IS_MESSAGE_SELECTED macro without
 * having to call a function. */
typedef struct msg_masks_t
{
	unsigned long m1;
	unsigned long m2;
} msg_masks_t;

/* module linked list record*/
typedef struct fmodule
{
	int slot;
	int readPipe;
	int writePipe;
	fqueue pipeQueue;
	msg_masks_t PipeMask;
	msg_masks_t NoGrabMask;
	msg_masks_t SyncMask;
	char *pipeName;
	char *pipeAlias;
	struct fmodule *next;
} fmodule;

/*
 * I needed sendconfig off  to  identify open  pipes that want  config
 * info messages while active.
 *
 * There really should be  a   module structure.  Ie.  the   "readPipes",
 * "writePipes", "pipeName", arrays  should be  members  of a  structure.
 * Probably a linklist of structures.  Note that if the OS number of file
 * descriptors   gets really  large,   the  current  architecture  starts
 * creating and looping  over  large arrays.  The  impact seems  to be in
 * module.c, modconf.c and event.c.  dje 10/2/98
 */

/* this is a bit long winded to allow MAX_MESSAGE to be 32 and not get an
 * integer overflow with (1 << MAX_MESSAGES) and even with
 * (1<<(MAX_MESSAGES-1)) - 1 */
#define DEFAULT_MASK   (MAX_MSG_MASK & ~(M_SENDCONFIG))
#define DEFAULT_XMASK  (DEFAULT_XMSG_MASK)

/*
 * Returns zero if the msg is not selected by the mask. Takes care of normal
 * and extended messages.
 */
#define IS_MESSAGE_IN_MASK(mask, msg) \
	(((msg)&M_EXTENDED_MSG) ? ((mask)->m2 & (msg)) : ((mask)->m1 & (msg)))

/*
 * Returns non zero if one of the specified messages is selected for the module
 */
#define IS_MESSAGE_SELECTED(module, msg_mask) \
	IS_MESSAGE_IN_MASK(&(module->PipeMask), (msg_mask))

/*
 * M_SENDCONFIG for   modules to tell  fvwm that  they  want to  see each
 * module configuration command as   it is entered.  Causes  modconf.c to
 * look at each active module, find  the ones that sent M_SENDCONFIG, and
 * send a copy of the command in an M_CONFIG_INFO command.
 */

fmodule *module_get_next(fmodule *prev);
void initModules(void);
Bool HandleModuleInput(Window w, fmodule *module, char *expect, Bool queue);
void KillModule(fmodule *module);
void ClosePipes(void);
void BroadcastPacket(unsigned long event_type, unsigned long num_datum, ...);
void BroadcastConfig(unsigned long event_type, const FvwmWindow *t);
void BroadcastName(
	unsigned long event_type, unsigned long data1,
	unsigned long data2, unsigned long data3, const char *name);
void BroadcastWindowIconNames(FvwmWindow *t, Bool window, Bool icon);
void BroadcastFvwmPicture(
	unsigned long event_type,
	unsigned long data1, unsigned long data2,
	unsigned long data3, FvwmPicture *picture, char *name);
void BroadcastPropertyChange(
	unsigned long argument, unsigned long data1,
	unsigned long data2, char *string);
void BroadcastColorset(int n);
void BroadcastConfigInfoString(char *string);
void broadcast_xinerama_state(void);
void broadcast_ignore_modifiers(void);

void SendPacket(
	fmodule *module, unsigned long event_type, unsigned long num_datum,
	...);
void SendConfig(
	fmodule *module, unsigned long event_type, const FvwmWindow *t);
void SendName(
	fmodule *module, unsigned long event_type, unsigned long data1,
	unsigned long data2, unsigned long data3, const char *name);
void FlushAllMessageQueues(void);
void FlushMessageQueue(fmodule *module);
void ExecuteCommandQueue(void);
void PositiveWrite(fmodule *module, unsigned long *ptr, int size);
RETSIGTYPE DeadPipe(int nonsense);
char *skipModuleAliasToken(const char *string);
fmodule *executeModuleDesperate(F_CMD_ARGS);
int is_message_selected(fmodule *module, unsigned long msg_mask);
int countModules(void);

#endif /* MODULE_H */
