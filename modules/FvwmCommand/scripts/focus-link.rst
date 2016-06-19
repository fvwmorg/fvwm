========================================================================
focus-link
========================================================================

------------------------------------------------------------------------
focus-link.pl - perl FvwmCommand script
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

focus-link.pl [-v]

OPTION
------

-v
  show version number and exit.

DESCRIPTION
-----------

This is a user programmable window focus script. It requires FvwmCommand
version 1.5 or later. FvwmCommandS must be invoked from fvwm prior to
this command.

This script can be invoked from a shell or from .fvwm2rc. For example.

::

    AddToFunc "InitFunction"
    + "I" Exec exec xcb -n 4 -l vertical -g 240x180-0+530
    + "I" Exec sleep 2; $HOME/scripts/focus-link.pl

Sleep is used in order to avoid un-necessary reaction during initial
window creation. Note, fvwm itself continues to run during these 2
seconds.

Default behavior is listed below. In order to change the behavior,
modify user\_function using user functions.

1. When a window is opened up, focus the window and move
   the pointer to it. The parent window regains focus when
   a window is closed. Parenthood is determined when a
   window is opened. It is the last focused window with the
   same X class.
2. #1 would not occur to AcroRead opening window.
3. #1 would not occur when SkipMapping is set and the
   window is the only window of its class.
4. For Netscape find dialog window, addition to #1, resize
   the window to 300x150 pixels and move it to East edge of
   the screen. Download/upload windows will not be focused
   nor be in focus link list.
5. Move appletviewer to NorthWest corner.
6. Xterm won\'t focus back to its parent after closed.
7. When a window is de-iconified, focus it and move the
   pointer.

USER FUNCTIONS
--------------

These are collection of functions a user can call from programmable
section.

**move\_window [<id>] <direction>** or **move\_window [<id>] <x> <y>**
    If <id> is prensent in hex format, then move <id> window. Otherwise,
    move the window in question.

    If <y> is present, move window to <x> <y> in percentage of screen.

    If \'p\' is appended to <width> or <height>, it specifies in pixel count.
    And, if <width\'p\'> or <height\'p\'> is lead with \'-\', it signifies that
    pixel count from right or bottom edge.

    If <y> does not exist, <dir> must be one of North Northeast East
    Southeast South Southwest West Northwest to move window to edge.

**resize\_window [<id>] <width> <height>**
    Resize window to <width> and <height> in percentage of screen size.

    If <id> is not null, resize <id>. Otherwise resize the window in
    question.

    Letter \'p\' can be appended to <width> and <height> to specify in pixel
    count.

**focus\_window [<id>]**
    If <id> is not null, focus on <id>. Otherwise, focus on the window in
    question.

**warp\_to\_window [<id>] [<x> <y>]**
    Move pointer to window.

    If <id> is a window id, warp to <id>. Otherwise, warp to the window in
    question.

    If <x> and <y> are present, warp to <x> and <y> percentage of window
    size down and in from the upper left hand corner.

    Letter \'p\' can be appended to <width> and <height> to specify in pixel
    count.

**class\_matches <class> [<resource>]**
    Check if window class and optional resource match.

    If arg1 is present, and if class matches with <class> and resource
    matches with <resource>, then return 1.

    If arg1 is not present, and if class matches with <class> then return 1.
    Otherwise, return null.

**window\_flag [<id>] <flag>**
    Return 1 if <flag> is true in the window in question. If <id> is not
    null, check on <id>. Otherwise check on the window in question. <flag>
    must be a exact match to one of these:
    
    ::
    
        StartIconic
        OnTop
        Sticky
        WindowListSkip
        SuppressIcon
        NoiconTitle
        Lenience
        StickyIcon
        CirculateSkipIcon
        CirculateSkip
        ClickToFocus
        SloppyFocus
        SkipMapping
        Handles
        Title
        Mapped
        Iconified
        Transient
        Visible
        IconOurs
        PixmapOurs
        ShapedIcon
        Maximized
        WmTakeFocus
        WmDeleteWindow
        IconMoved
        IconUnmapped
        MapPending
        HintOverride
        MWMButtons
        MWMBorders

**resource\_matches <resource>**
    Check if window resource matches pattern <resource>. If it matches,
    return 1. Otherwise return null.

**action\_was <action>**
    Check if <action> was taken place.

    <action> must be a exact match to one of these:

    ::

        new page
        new desk
        add
        raise
        lower
        focus change
        destroy
        iconify
        deiconify
        windowshade
        dewindowshade
        end windowlist
        icon location
        end configinfo
        string

**get\_parent\_window [<id>]**
    Return parent window id.

    If <id> is not null, check on <id>. Otherwise check on the window in
    question.

**no\_parent\_window [<id>]**
    Return 1 if no parent window exits.

    If <id> is not null, check on <id>. Otherwise check on the window in
    question.

**delete\_from\_list**
    Delete the window from link list

SEE ALSO
--------

FvwmCommand

AUTHOR
------

Toshi Isogai isogai@ucsub.colorado.edu
