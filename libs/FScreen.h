/* -*-c-*- */
#ifndef FVWMLIB_FSCRREN_H
#define FVWMLIB_FSCRREN_H

/* needs X11/Xlib.h and X11/Xutil.h */

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

#define FSCREEN_MANGLE_USPOS_HINTS_MAGIC ((short)-32109)


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
int FScreenNumberOfScreens(void);

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
