========================================================================
fvwm-menu-xlock
========================================================================

------------------------------------------------------------------------
builds xlock menu definition for fvwm
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

**fvwm-menu-xlock** [ **\-\-help**\ \|\ **\-h**\ \|\ **\-?** ] [
**\-\-version**\ \|\ **\-V** ] [ **\-\-name**\ \|\ **\-n** name ] [
**\-\-title**\ \|\ **\-t** title ] [ **\-\-item** format ] [ **\-\-icon\-title**
icon ] [ **\-\-icon\-item** icon ] [ **\-\-special\-first**\ \|\ **\-s** ] [ --
xlock params ]

DESCRIPTION
-----------

A simple perl script which parses xlock\'s output to build an fvwm menu
definition of all xlock\'s modes.

OPTIONS
-------

**\-\-help**
    show the help and exit

**\-\-version**
    show the version and exit

**\-\-name** name
    define menu name in the following argument. Default is "XLockMenu"

**\-\-title** title
    define menu title in the following argument. Default is "XLock Modes".

**\-\-item** format
    define menu item format in the following argument, default is
    \'%n\\t(%d)\'. TAB can be specified as \'\\t\', but in .fvwm2rc you should
    specify a double backslash or a real TAB .

    Format specifiers:

    ::

        %n - mode name
        %d - mode description
        %D - mode description without "Shows " prefix if any

    These specifiers can receive an optional integer size, positive for
    right adjusted string or negative for left adjusted, example: ``%8x``;
    and optional \*num or \*\-num, which means to leave only the first or
    last (if minus) num of chars, the num must be greater than 3, since the
    striped part is replaced with "...", example: %\*30x. Both can be
    combined: %\-10\*\-20x, this instructs to get only the 20 last characters,
    but if the length is less then 10 \- to fill with up to 10 spaces on the
    right.

**\-\-icon\-title** icon **\-\-icon\-item** icon
    define menu icon for title and regular item accordingly. Default is no
    menu icons (equivalent to an empty icon argument).

**\-\-wm\-icons**
    define icon names suitable for use with wm-icons package. Currently this
    is equivalent to: \-\-icon\-title \'\' \-\-icon\-item menu/lock.xpm.

**\-\-special\-first**
    instructs to include special modes (usually black, bomb and random)
    first.

Option parameters can be specified either using \'=\' or in the next
argument. Short options are ok if not ambiguous: \-h, \-t; but be careful
with short options, what is now unambiguous, can became ambiguous in the
next versions.

Additional arguments (after **\-\-**) will be passed to xlock.

Please see the **xlock**\ (1) man page for the xlock options.

USAGE
-----

Add these lines to your fvwm configuration file:

::

    PipeRead 'fvwm-menu-xlock --name MenuSSaver --title "Screensaver" \
    --icon-item mini-bball.xpm --special-first -- -nice 19 -nolock'
    PipeRead 'fvwm-menu-xlock --name MenuSLock --title "Lock Screen" \
    --icon-item mini-rball.xpm --special-first -- -nice 19'
    AddToMenu "Utilities" "Screensaver%mini-monitor.xpm%" Popup MenuSSaver
    AddToMenu "Utilities" "Screenlock%mini-lock.xpm%"     Popup MenuSLock

AUTHORS
-------

Charles K. Hines <chuck\_hines@vnet.ibm.com>, initial version.

Mikhael Goikhman <migo@homemail.com>, from 24 Feb 1999.

COPYING
-------

The script is distributed by the same terms as fvwm itself. See GNU
General Public License for details.

BUGS
----

Depends on the output of xlock. Will produce an empty menu if the
structure of the output is changed.

Report bugs to fvwm\-bug@fvwm.org.
