========================================================================
FvwmPager
========================================================================

------------------------------------------------------------------------
the Fvwm Pager module
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

**FvwmPager** [ *-transient* ] [ *name* ] [ *first desk* [ *last desk* ]
] FvwmPager is spawned by fvwm, so no command line invocation will work.

All desks with desk numbers between *first desk* and *last desk* are
displayed. If *last desk* is omitted only the *first desk* is shown. If
both desk numbers are omitted, the current desk is used instead. If you
use an asterisk \'\*\' in place of *first desk* the pager will always show
the current desktop, even when you switch desks.

Example lines to put in your .fvwm2rc:

::

    Module FvwmPager 0 3

or

::

    Module FvwmPager *

or from within an fvwm pop-up menu:

::

    AddToMenu Module-Popup Modules Title
    + Audio     Module FvwmAudio
    + Auto      Module FvwmAuto 200
    + Buttons   Module FvwmButtons
    + Console   Module FvwmConsole
    + Ident     Module FvwmIdent
    + Banner    Module FvwmBanner
    + Pager     Module FvwmPager 0 3

or

::

    + Pager     Module FvwmPager *

If the pager is started with the *-transient* option, the next time a
button is released the pager is closed. Note that this option does only
work if the window style of the pager window is \'sticky\' (see the fvwm
man page). You should use the \'StaysOnTop\' style too.

Example:

::

    Style FvwmPager Sticky, StaysOnTop
    *FvwmPager: Rows 1
    *FvwmPager: Columns 1
    Mouse 3 R C Module FvwmPager -transient

With this in your .fvwm2rc, if you press control and button 3 in the
root window the pager pops up under the mouse and while the viewport
moves with the mouse.

DESCRIPTION
-----------

The FvwmPager module shows a miniature view of the Fvwm desktops which
are specified in the command line. This is a useful reminder of where
your active windows are. Windows in the pager are shown in the same
color as their fvwm decorations.

The pager can be used to change your viewport into the current desktop,
to change desktops, or to move windows around.

Pressing mouse button 1 in the pager will cause you viewport to change
to the selected page of the selected desk. If you click with button 1 in
the desk-label area, you will switch desks but not pages within the
desk.

Dragging mouse button 2 on a miniature view of a window will cause that
window to be move to the location where you release the mouse button,
but your viewport will not change. If you drag the window out of the
pager and onto your desktop, a full size image of the window will appear
for you to place. There is no way to pick up a full size image of the
window and move it into the pager, however. Since some mice do not have
button 2, I have made provisions to drag windows in the pager by using
pressing modifier-1 (usually Alt) and dragging with button 3.

Clicking mouse button 3 on a location will cause the viewport to move to
the selected location and switch desks if necessary, but will not align
the viewport to a page boundary. Dragging button 3 will cause the
viewport to move as you drag but not switch desktops, even if the
pointer moves to another desktop.

With the *\*FvwmPager: SloppyFocus* option the focus is transferred to
the window pointed at with the mouse when the pointer is inside the
pager.

When iconified, the pager will work as a fully functional current desk
only pager. Windows and viewports can be moved within the icon of the
pager. Users will want to make sure that they have no lines similar to

::

    Icon "Fvwm Pager" whatever

in their .fvwm2rc files.

COPYRIGHTS
----------

The FvwmPager program, and the concept for interfacing this module to
the Window Manager, are all original work by Robert Nation.

Copyright 1994, Robert Nation. No guarantees or warranties or anything
are provided or implied in any way whatsoever. Use this program at your
own risk. Permission to use this program for any purpose is given, as
long as the copyright is kept intact.

INITIALIZATION
--------------

During initialization, *FvwmPager* gets config info from **fvwm**\ \'s
module configuration database (see *fvwm*\ (1), section **MODULE
COMMANDS**).

To use FvwmPager with several different configurations, you can invoke
FvwmPager with an optional parameter, which it will use as its *name*
instead (e.g "Module FvwmPager OtherPager"). OtherPager will then read
only the lines in the configuration file starting with "\*OtherPager",
and not the lines belonging to FvwmPager. This way multiple pager
instances may be used.

Note: the old way to use the FvwmPager with several different
configurations is to link the executable to another name, i.e.

::

    ln -s FvwmPager OtherPager

This may work, but this method is not supported.

KEYBOARD FOCUS CONTROL
----------------------

You can direct the keyboard focus to any window on the current desktop
by clicking with button 2 on its image in the pager. The window does not
need to be visible, but it does need to be on the current page.

INVOCATION
----------

The invocation method was shown in the synopsis section

CONFIGURATION OPTIONS
---------------------

\*FvwmPager: Geometry *geometry*
    Completely or partially specifies the pager windows location and
    geometry, in standard X11 notation. In order to maintain an undistorted
    aspect ratio, you might want to leave out either the width or height
    dimension of the geometry specification.

\*FvwmPager: Rows *rows*
    Tells fvwm how many rows of desks to use when laying out the pager
    window.

\*FvwmPager: Columns *columns*
    Tells fvwm how many columns of desks to use when laying out the pager
    window.

\*FvwmPager: IconGeometry *geometry*
    Specifies a size (optional) and location (optional) for the pager\'s icon
    window. Since there is no easy way for FvwmPager to determine the height
    of the icon\'s label, you will have to make an allowance for the icon
    label height when using negative y-coordinates in the icon location
    specification (used to specify a location relative to the bottom instead
    of the top of the screen).

\*FvwmPager: StartIconic
    Causes the pager to start iconified.

\*FvwmPager: NoStartIconic
    Causes the pager to start normally. Useful for canceling the effect of
    the *StartIconic* option.

\*FvwmPager: LabelsBelow
    Causes the pager to draw desk labels below the corresponding desk.

\*FvwmPager: LabelsAbove
    Causes the pager to draw desk labels above the corresponding desk.
    Useful for canceling the effect of the *LabelsBelow* option.

\*FvwmPager: ShapeLabels
    Causes the pager to hide the labels of all but the current desk. This
    turns off label hilighting.

\*FvwmPager: NoShapeLabels
    Causes the pager to show the labels of all visible desks. Useful for
    canceling the effect of the *ShapeLabels* option.

\*FvwmPager: Font *font-name*
    Specified a font to use to label the desktops. If *font\_name* is "none"
    then no desktop labels will be displayed.

\*FvwmPager: SmallFont *font-name*
    Specified a font to use to label the window names in the pager. If not
    specified, the window labels will be omitted. Window labels seem to be
    fairly useless for desktop scales of 32 or greater. If *font\_name* is
    "none" then no window names will be displayed.

\*FvwmPager: Fore *color*
    Specifies the color to use to write the desktop labels, and to draw the
    page-grid lines.

\*FvwmPager: Back *color*
    Specifies the background color for the window.

\*FvwmPager: Hilight *color*
    The active page and desk label will be highlighted by using this
    background pattern instead of the normal background.

\*FvwmPager: HilightPixmap *pixmap*
    The active page will be highlighted by using this background pattern
    instead of the normal background.

\*FvwmPager: DeskHilight
    Hilight the active page with the current hilight color/pixmap. Useful
    for canceling the effect of the *NoDeskHilight* option.

\*FvwmPager: NoDeskHilight
    Don\'t hilight the active page.

\*FvwmPager: WindowColors *fore back hiFore hiBack*
    Change the normal/highlight colors of the windows. *fore* and *hiFore*
    specify the colors as used for the font inside the windows. *back* and
    *hiBack* are used to fill the windows with.

\*FvwmPager: WindowLabelFormat *format*
    This specifies a printf() like format for the labels in the mini window.
    Possible flags are: %t, %i, %c, and %r for the window\'s title, icon
    title, class, or resource name, respectively. The default is "%i".

\*FvwmPager: Label *desk label*
    Assigns the text *label* to desk *desk* (or the current desk if desk is
    "\*") in the pager window. Useful for assigning symbolic names to
    desktops, i.e.

    ::

        *FvwmPager: Label 1 Mail
        *FvwmPager: Label 2 Maker
        *FvwmPager: Label * Matlab

    **Note**: There is currently a much better way to specify desk names
    globally (and not just in FvwmPager) using **DesktopName** command, so
    you should not use this option anymore.

\*FvwmPager: DeskColor *desk color*
    Assigns the color *color* to desk *desk* (or the current desk if desk is
    "\*") in the pager window. This replaces the background color for the
    particular *desk*. This only works when the pager is full sized. When
    Iconified, the pager uses the color specified by \*FvwmPager: Back.

    **TIP:** Try using \*FvwmPager: DeskColor in conjunction with FvwmCpp
    (or FvwmM4) and FvwmBacker to assign identical colors to your various
    desktops and the pager representations.

\*FvwmPager: Pixmap *pixmap*
    Use *pixmap* as background for the pager.

\*FvwmPager: DeskPixmap *desk pixmap*
    Assigns the pixmap *color* to desk *desk* (or the current desk if desk
    is "\*") in the pager window. This replaces the background pixmap for
    the particular *desk*.

    **TIP:** Try using \*FvwmPager: DeskPixmap in conjunction with FvwmCpp
    (or FvwmM4) and FvwmBacker to assign identical pixmaps to your various
    desktops and the pager representations.

\*FvwmPager: DeskTopScale *number*
    If the geometry is not specified, then a desktop reduction factor is
    used to calculate the pager\'s size. Things in the pager window are shown
    at 1/\ *number* of the actual size.

\*FvwmPager: MiniIcons
    Allow the pager to display a window\'s mini icon in the pager, if it has
    one, instead of showing the window\'s name.

\*FvwmPager: MoveThreshold *pixels*
    Defines the distance the pointer has to be moved before a window being
    dragged with button 2 is actually moved. The default value is three
    pixels. If the pointer moved less that this amount the window snaps back
    to its original position when the button is released. If *pixels* is
    less than zero the default value is used. The value set with the
    *MoveThreshold* command in fvwm is inherited by FvwmPager but can be
    overridden with this option.

\*FvwmPager: SloppyFocus
    If the SloppyFocus option is used, you do not need to click into
    the  mini window in the pager to give the real window the focus.
    Simply putting the pointer over the window inside the  pager  is
    enough.

    **Note:** This option interferes slightly with the MouseFocus and
    SloppyFocus styles of fvwm. Sometimes, if you click into the
    pager window to change pages or desks and then move the
    pointer   to a place on the screen where a window of the new
    page will appear, this new window does not get the input focus.
    This may happen if you drag the pointer over one of the mini
    windows in the pager. There is nothing that can be done about
    this - except not using SloppyFocus in the pager.

\*FvwmPager: SolidSeparators
    By default the pages of the virtual desktop are separated by dashed
    lines in the pager window. This option causes FvwmPager to use solid
    lines instead.

\*FvwmPager: NoSeparators
    Turns off the lines separating the pages of the virtual desktop.

\*FvwmPager: Balloons [*type*]
    Show a balloon describing the window when the pointer is moved into a
    window in the pager. The default format (the window\'s icon name) can be
    changed using BalloonStringFormat. If *type* is *Pager* balloons are
    just shown for an un-iconified pager; if *type* is *Icon* balloons are
    just shown for an iconified pager. If *type* is anything else (or null)
    balloons are always shown.

\*FvwmPager: BalloonFore *color*
    Specifies the color for text in the balloon window. If omitted it
    defaults to the foreground color for the window being described.

\*FvwmPager: BalloonBack *color*
    Specifies the background color for the balloon window. If omitted it
    defaults to the background color for the window being described.

\*FvwmPager: BalloonFont *font-name*
    Specifies a font to use for the balloon text. Defaults to *fixed*.

\*FvwmPager: BalloonBorderWidth *number*
    Sets the width of the balloon window\'s border. Defaults to 1.

\*FvwmPager: BalloonBorderColor *color*
    Sets the color of the balloon window\'s border. Defaults to black.

\*FvwmPager: BalloonYOffset *number*
    The balloon window is positioned to be horizontally centered against the
    pager window it is describing. The vertical position may be set as an
    offset. Negative offsets of *-n* are placed *n* pixels above the pager
    window, positive offsets of *+n* are placed *n* pixels below. Offsets of
    -1 and 1 represent the balloon window close to the original window
    without a gap. Offsets of 0 are not permitted, as this would permit
    direct transit from pager window to balloon window, causing an event
    loop. Defaults to +3. The offset will change sign automatically, as
    needed, to keep the balloon on the screen.

\*FvwmPager: BalloonStringFormat format
    The same as *\*FvwmPager: WindowLabelFormat*, it just specifies the
    string to display in the balloons. The default is "%i".

\*FvwmPager: Colorset *desk colorset*
    Tells the module to use colorset *colorset* for *desk*. If you use an
    asterisk \'\*\' in place of *desk*, the colorset is used on all desks.
    Please refer to the man page of the FvwmTheme module for details about
    colorsets.

\*FvwmPager: BalloonColorset *desk colorset*
    Tells the module to use colorset *colorset* for balloons on *desk*. If
    you use an asterisk \'\*\' in place of *desk*, the colorset is used on all
    desks. Please refer to the man page of the FvwmTheme module for details
    about colorsets.

\*FvwmPager: HilightColorset *desk colorset*
    Tells the module to use colorset *colorset* for hilighting on *desk*. If
    you use an asterisk \'\*\' in place of *desk*, the colorset is used on all
    desks. Please refer to the man page of the FvwmTheme module for details
    about colorsets.

\*FvwmPager: WindowColorsets *colorset activecolorset*
    Uses colorsets in the same way as \*FvwmPager: WindowColors. Please
    refer to the man page of the FvwmTheme module for details about
    colorsets. The shadow and hilight colors of the colorset are only used
    for the window borders if the \*FvwmPager: Window3DBorders is specified
    too.

\*FvwmPager: WindowBorderWidth *n*
    Specifies the width of the border drawn around the mini windows. This
    also sets the minimum size of the mini windows to (2 \* *n* + 1). The
    default is 1.

\*FvwmPager: Window3DBorders
    Specifies that the mini windows should have a 3d borders based on the
    mini window background. This option only works if \*FvwmPager:
    WindowColorsets is specified.

\*FvwmPager: UseSkipList
    Tells FvwmPager to not show the windows that are using the
    WindowListSkip style.

AUTHOR
------

| Robert Nation
| DeskColor patch contributed by Alan Wild
| MiniIcons & WindowColors patch contributed by Rob Whapham
| Balloons patch by Ric Lister <ric@giccs.georgetown.edu>
| fvwm-workers: Dominik, Olivier, Hippo and others.
