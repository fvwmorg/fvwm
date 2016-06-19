========================================================================
FvwmProxy
========================================================================

------------------------------------------------------------------------
the fvwm proxy module
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

FvwmProxy is spawned by fvwm, so no command line invocation will work.

DESCRIPTION
-----------

The FvwmProxy allows the user to locate and control windows obscured by
other windows by using small non-overlapping proxy windows. The default
capabilities include raising and lowering the proxied windows.

Using the sample configuration, pressing Alt-Tab cycles through the
windows and allows the use of assignable click actions on the proxies.
Releasing the Alt key deactivates the proxy windows. By default,
pressing the left or right mouse buttons on a proxy window raises or
lowers the associated proxied window respectively. An additional mapping
can have the proxies automatically appear by just holding the Alt key.

Proxy windows are always on top and try to center on the regular window
they proxy. A simple collision algorithm tweaks the positions of the
proxy windows to prevent them from overlapping.

COPYRIGHTS
----------

The FvwmProxy program is original work by Jason Weber.

Copyright 2002, Jason Weber. No guarantees or warranties or anything are
provided or implied in any way whatsoever. Use this program at your own
risk.

INVOCATION
----------

FvwmProxy can be invoked by inserting the line \'Module FvwmProxy\' in the
.fvwm2rc file. This can be placed on a line by itself, if FvwmProxy is
to be spawned during fvwm\'s initialization, or can be bound to a menu or
mouse button or keystroke to invoke it later. Fvwm will search directory
specified in the ModulePath configuration option to attempt to locate
FvwmProxy.

CONFIGURATION OPTIONS
---------------------

\*FvwmProxy: Colorset *n*
    Specifies the color theme for unselected proxy windows.

\*FvwmProxy: SelectColorset *n*
    Specifies the color theme for the selected proxy window.

\*FvwmProxy: IconifiedColorset *n*
    Specifies the color theme for proxy windows of iconified windows. This
    is only meaningful in conjunction with the ProxyIconified option on.

\*FvwmProxy: Font *font*
    Specifies the font used for large proxy window text. This usually
    contains the icon string and is nearly vertically centered in the proxy.
    If there is no icon string, the title bar string is used. If this text
    exceeds the width of the proxy, it is cropped on the right. If no Font
    is specified, a default is used.

\*FvwmProxy: SmallFont *font*
    Specifies the font used for the auxillary proxy window text. This
    usually contains the title bar string, but is omitted if it is identical
    to the icon string and that text was not cropped. The text is drawn
    close to the bottom of the proxy and should probably be the smallest
    legible font available. If this text exceeds the width of the proxy, it
    is cropped on the left. If no SmallFont is specified, this text is never
    drawn.

\*FvwmProxy: Width *w*
    Specifies the size in X of each proxy window. The default is 180.

\*FvwmProxy: Height *h*
    Specifies the size in Y of each proxy window. The default is 60.

\*FvwmProxy: Separation *d*
    Specifies the minimum distance between proxy windows when adjusting for
    collisions. The default is 10.

\*FvwmProxy: ShowMiniIcons *bool*
    If true, proxy windows show the mini icon for the window they represent,
    if it has a mini icon. The default is true.

\*FvwmProxy: EnterSelect *bool*
    If true, a proxy is automatically selected when the mouse is moved over
    the proxy, even if no mouse buttons are pressed. The default is false.

\*FvwmProxy: ProxyMove *bool*
    If true, moving a proxy window will move the window it represents.
    Currently, the proxied window doesn\'t recognize snap effects during this
    operation. The default is false.

\*FvwmProxy: ProxyIconified *bool*
    If true, continue to show proxy windows when they are iconified. In
    addition, consider adding click actions that Iconify on and off, such as
    on the middlemouse button. The default is false.

\*FvwmProxy: ShowOnly *mode*
    Limits the appearance of proxy windows during the Show action. The
    supported modes are Selected, Covered, Grouped, and All. The default is
    All which shows every proxy window on the current desk. Select mode will
    only show the proxy window for the selected window. If no window is
    selected, the currently focused window is treated as the select window
    for ShowOnly filtering. Covered mode extends Select mode to add proxy
    windows that overlap the select real window. Just using Selected mode
    can result in untouchable proxy windows that disappear before you can
    reach them. Grouped mode extends Covered mode to show proxy windows in
    the same window group as the selected window. In all cases, iconified
    proxy windows never appear if ProxyIconified is false.

\*FvwmProxy: Action *mouseaction response*
    Tells FvwmProxy to do the specified *response* when the given *action*
    is done. The currently supported mouse actions are: Click1, Click2,
    Click3 and so on, representing mouse clicks with various buttons. By
    default, the module supports 3 mouse buttons, but it can be compiled to
    support more. The default responses are Raise, Nop, and Lower for
    Click1, Click2, and Click3, respectively.

\*FvwmProxy: Action Select *command*
    This selects an fvwm function to be called during a FvwmProxy Hide
    command for the window whose proxy was selected. The default is
    WindowListFunc. WindowListFunc is predefined by the fvwm install. You
    can replace it, add to it, or supply an independent function.

\*FvwmProxy: Action Show *command*
    This selects an fvwm function to be called during a FvwmProxy Show
    command. The default is Nop.

\*FvwmProxy: Action Hide *command*
    This selects an fvwm function to be called during a FvwmProxy Hide
    command. The default is Nop.

\*FvwmProxy: Action Abort *command*
    This selects an fvwm function to be called during a FvwmProxy Abort
    command. The default is Nop.

\*FvwmProxy: Action Mark *command*
    This selects an fvwm function to be called on a window after it is
    marked. The default is Nop.

\*FvwmProxy: Action Unmark *command*
    This selects an fvwm function to be called on a marked window just after
    another window gets the mark. The default is Nop.

\*FvwmProxy: Action ModifierRelease *modifiers command*
    This selects an fvwm function to be called while proxies are shown and
    the specified modifiers are all released. The modifiers are specified
    using the same syntax as in the Mouse command. The default is Nop.

\*FvwmProxy: Group *groupname command pattern*
    For the given named group, adjust inclusion of the windows matching the
    pattern. The groupname is a string identifier used to associate windows.
    The window pattern uses the same format as the Style command. The
    supported commands are Include, SoftInclude, WeakInclude,
    WeakSoftInclude, and Exclude. The commands ending in Include identify a
    pattern to add windows to the group. Exclude identifies pattern to
    counteract inclusion pattern or auto-inclusion (see flags below). All
    exclusion checks follow all inclusion checks. Soft inclusion limits the
    windows in that pattern to only move when an non-soft window in the
    group moves. Moving or resizing these windows does not affect any other
    windows. They are also immune to edge effects. Soft inclusion also
    affects provocation effects (see below). Weak inclusion prevents
    inclusion purely on name, instead relying on X11 leader or process id
    matching. Weakly included names will not start a group, but will join a
    group in the same known process or with the same leader. Once the window
    has joined, the name is just used to determine if the inclusion is soft.

\*FvwmProxy: Group *groupname flag*
    For the given named group, activate the given flag. The supported flags
    are AutoInclude, AutoSoft, and IgnoreIDs. All window grouping is
    normally checked to only group windows that are in the same process or
    that have the same X11 client leader. IgnoreIDs deactivates this
    mechanism. AutoInclude automatically includes any window that matches
    the same process or client leader, without having to name them
    specifically. AutoSoft makes all AutoInclusions soft (see inclusion
    description above).

\*FvwmProxy: Group *groupname provocation pattern*
    The provocation flags allow you to customize whether grouped windows
    provoke each other in response to a raise/lower, desk move, drag, or
    iconification change. The compound provocation flag is of the form
    (No\|Inherit)(Hard\|Soft)(Raise\|Desk\|Drag\|Icon\|All). The pattern is
    optional and should already have been included. The pattern limits the
    change to only affect that part of the group. The first element of the
    flag is optional and can turn off the effect, or, with a pattern, can
    dynamically inherit the setting for the group. The default is to turn
    the effect on. The second element can be used to only apply the change
    to windows with the soft state either on or off. The default is to
    change both. The third element specifies what provoking effect is being
    changed: window raise/lower, moving to another desk, dragging windows
    together, toggling iconification, or all of these. If either the
    provoking window or a potentially provoked window has an effect turned
    off, the provocation does not occur.

\*FvwmProxy: SlotWidth *w*
    This specifies the width of the icons used in slots. The default is 16.

\*FvwmProxy: SlotHeight *h*
    This specifies the height of the icons used in slots. The default is 16.

\*FvwmProxy: SlotSpace *d*
    This specifies the space between icons used in slots. The default is 4.

\*FvwmProxy: GroupSlot *n*
    This specifies the first slot that represent a colored group. Group
    slots don\'t need icons as the are drawn by predetermined means. The
    default is 2.

\*FvwmProxy: GroupCount *n*
    This specifies the number of group slots. The default is 6.

\*FvwmProxy: SlotStyle *n style*
    For non-group slots, this defines the appears of the indicated slot. The
    style format matches ButtonStyle command. The default is nothing.

\*FvwmProxy: SlotAction *n mouseaction response*
    For non-group slots, this defines the behavior of the indicated slot.
    The mouse action and response is used the same as the FvwmProxy Action
    configuration. The default is Nop.

\*FvwmProxy: UndoLimit *n*
    This specifies the number of entries in the undo buffer. this limits how
    far back you can undo. The default is 8.

COMMANDS
--------

SendToModule FvwmProxy Show
    Activate proxy windows for all windows on the current desk that do not
    use the WindowListSkip option. If the desk is switched, new proxies are
    automatically generated.

SendToModule FvwmProxy Hide
    Deactivate all proxy windows. If a proxy is selected (such as with the
    Next and Prev commands), the Select Action is call on the window that
    the proxy represents. The default action includes raising the window and
    warping the mouse to a position over that window.

SendToModule FvwmProxy ShowToggle
    If shown, hide. If hidden, show.

SendToModule FvwmProxy Abort
    Deactivate all proxy windows. This differs from the Hide command in that
    no action is taken on any selected window.

SendToModule FvwmProxy Circulate *command*
    Tell FvwmProxy to run a conditional command and mark the result. The
    imbedded command *SendToModule FvwmProxy Mark* is automatically appended
    after the optional condition, so supplying your own imbedded command
    will probably fail. An example argument to Circulate is *ScanForWindow
    East South (CurrentPage)*. If the proxies aren\'t already shown (such as
    with the Show command), any Circulate command will automatically show
    the proxies.

SendToModule FvwmProxy Next (obsolete)
    If a proxy window is selected, the next proxy is selected. Windows with
    the WindowListSkip option are ignored. The proxies are sorted left to
    right during the Show command. If no proxy is currently selected, but a
    proxy on this desk was selected on a recent show, that proxy is
    selected. If no proxy on this desk was recently selected, the leftmost
    proxy is used. This nearly duplicates the functionality of Circulate
    ScanForWindow East South (CurrentPage).

SendToModule FvwmProxy Prev (obsolete)
    If a proxy window is selected, the previous proxy is selected. The
    starting point is the same as with the Next command, except that the
    choice with no recent selection is the rightmost proxy. This nearly
    duplicates the functionality of Circulate ScanForWindow West North
    (CurrentPage).

SendToModule FvwmProxy SoftToggle
    Toggle the soft group inclusion setting for the selected window. This
    setting is the same that can be activated using the SoftInclude and
    AutoSoft commands inside the FvwmProxy Group configuration.

SendToModule FvwmProxy IsolateToggle
    Toggle the isolation setting for the selected window\'s group. Isolated
    groups only allow one member to not be iconified at a time. The members
    are also coerced to the same position and size, constrained by their
    size increment.

SendToModule FvwmProxy PrevIsolated
    If focused on a member of a isolating group, deiconify the member higher
    on list. If no member is higher, deiconify the last member.

SendToModule FvwmProxy NextIsolated
    If focused on a member of a isolating group, deiconify the member lower
    on list. If no member is higher, deiconify the first member.

SendToModule FvwmProxy Undo
    Attempt to undo the last window move and/or resize.

SendToModule FvwmProxy Redo
    Attempt to redo the most recent Undo. If another move or resize occurs
    since the previous undo, the redo buffer will be cleared.

SAMPLE CONFIGURATION
--------------------

The following are excerpts from a .fvwm2rc file which describe FvwmProxy
initialization commands:

::

    Key Tab A M SendToModule FvwmProxy Circulate \
        ScanForWindow East South (CurrentPage)
    Key Tab A SM SendToModule FvwmProxy Circulate \
        ScanForWindow West North (CurrentPage)

    *FvwmProxy: Action ModifierRelease M SendToModule FvwmProxy Hide

But Meta-Shift-Tab can be awkward, so Meta-Q may be a better
alternative.

::

    Key Q A M SendToModule FvwmProxy Circulate \
        ScanForWindow West North (CurrentPage)

You might consider adding !Sticky to the (CurrentPage) conditional if
you use Sticky for low-interactivity programs, like load meters and
music players.

To have the proxies immediately pop up when you hold the Alt key, add

::

    Key Meta_L A N SendToModule FvwmProxy Show

If that\'s too intrusive, you can assign Alt-Esc to switch the proxies on
and off by adding

::

    Key Escape A M SendToModule FvwmProxy ShowToggle

Some platforms have problems where general Alt key combinations becoming
otherwise dysfunctional after defining these mappings. If this happens,
it might be difficult to take full advantage of this module.

To have the mouse jump to the center instead of the upper left corner,
try adding

::

    AddToFunc WindowListFunc
    + I WarpToWindow 50 50

or just make your own list function from scratch, for example

::

    DestroyFunc WindowListFunc
    AddToFunc WindowListFunc
    + I WindowId $[w.id] Raise
    + I WindowId $[w.id] WarpToWindow 50 50

Note that the default configuration does not activate any Next/Prev
operations for Alt-Tab since that sequence is, by default, used by
another module. Adding appropriate key mappings to your .fvwm2rc will
switch this responsibility to FvwmProxy.

If you use ProxyIconified, you might consider adding Iconify actions.

::

    AddToFunc WindowListFunc
    + I WindowId $[w.id] Iconify Off
    
    AddToFunc Raise-and-Deiconify
    + I WindowId $[w.id] Raise
    + I WindowId $[w.id] Iconify Off
    
    *FvwmProxy: Action Click1 Raise-and-Deiconify
    *FvwmProxy: Action Click2 Iconify

You can set up some basic slots fairly easily.

::

    *FvwmProxy: GroupSlot 2
    *FvwmProxy: GroupCount 5
    
    *FvwmProxy: SlotStyle 1 MiniIcon
    *FvwmProxy: SlotStyle 7 Pixmap "squeeze.xpm"
    *FvwmProxy: SlotStyle 8 Pixmap "mini-up.xpm"
    *FvwmProxy: SlotStyle 9 Pixmap "mini-bball.xpm"
    *FvwmProxy: SlotStyle 10 Pixmap "mini-cross.xpm"
    
    *FvwmProxy: SlotAction 1 Click1 Popup WindowMenu
    *FvwmProxy: SlotAction 7 Click1 SendToModule FvwmProxy IsolateToggle
    *FvwmProxy: SlotAction 8 Click1 SendToModule FvwmProxy SoftToggle
    *FvwmProxy: SlotAction 9 Click1 Iconify
    *FvwmProxy: SlotAction 10 Click1 Delete

In this example, WindowMenu is something you would have to define. If
your proxy width is too small, some slots can get cut off.

Undo and redo can be easily mapped to any keys.

::

    Key Z A 3 SendToModule FvwmProxy Undo
    Key R A 3 SendToModule FvwmProxy Redo

You can rotate through an isolated group using any keys. For example,
meta cursor-up and cursor-down could traverse the group.

::

    Key Up A 3 SendToModule FvwmProxy PrevIsolated
    Key Down A 3 SendToModule FvwmProxy NextIsolated

A somewhat impractical example of a group definition using GIMP is as
follows:

::

    *FvwmProxy: Group "GIMP" Include "The GIMP"
    *FvwmProxy: Group "GIMP" Include "Module Manager"
    *FvwmProxy: Group "GIMP" SoftInclude "Unit Editor"
    *FvwmProxy: Group "GIMP" AutoInclude
    *FvwmProxy: Group "GIMP" AutoSoft
    *FvwmProxy: Group "GIMP" Exclude "Preferences"

This sets up a hard attachment between the windows "The GIMP" and
"Module Manager". The "Unit Editor" is also in the group, but only
responds to movement of one of the hard inclusions. Any window in the
same process or with the same client leader is also associated, but they
default to soft inclusion, except "Preferences" which is explicitly
excluded. Note that in this case, the explicit soft inclusion of "Unit
Editor" is redundant with the combination of AutoInclude and AutoSoft.
However, if AutoSoft was not specified, the explicit SoftInclude would
distinguish that pattern from the otherwise hard inclusion under just
AutoInclude.

AUTHOR
------

Jason Weber
