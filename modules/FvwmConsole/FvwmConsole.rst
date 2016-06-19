========================================================================
FvwmConsole
========================================================================

------------------------------------------------------------------------
an fvwm command input interface
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

Module FvwmConsole [options]

*FvwmConsole* can only be invoked by fvwm. Command line invocation of
the *FvwmConsole* module will not work.

DESCRIPTION
-----------

FvwmConsole allows the user to type fvwm configuration commands
interactively, and have them executed immediately. This tool is
particularly useful for testing new configuration ideas, or for
implementing temporary changes to your environment.

INVOCATION
----------

FvwmConsole must be spawned as a module by fvwm. FvwmConsole takes all
*xterm*\ (1) options.

FvwmConsole can be invoked by inserting the line \'Module FvwmConsole\' in
the .fvwm2rc file. This can be placed on a line by itself, if
FvwmConsole is to be spawned during fvwm\'s initialization, or can be
bound to a menu or mouse button or keystroke to invoke it later.

CONFIGURATION OPTIONS
---------------------

FvwmConsole uses *xterm*\ (1). All resources set for xterm are inherited
unless overridden by command line options.

::

  Module FvwmConsole -g 40x10 -fg black -bg green3

A different terminal emulator can be specified with the -terminal
option. However, only terminal programs that understand the options
-name, -title and -e can be used.

::

  Module FvwmConsole -terminal rxvt

Previous versions of FvwmConsole supported a -e option to choose a
different front-end. Although this option is still provided for
backwards compatibility its use is discouraged unless you know exactly
what you are doing.

::

  Module FvwmConsole -e FvwmConsoleC.pl

(see *FvwmConsoleC.pl*\ (1)).

Also X resources can be set in your ~/.Xdefaults file:

::

  FvwmConsole\*VT100\*geometry: 40x4
  FvwmConsole\*font: 7x14

COMMAND EDITING
---------------

There are a few options. If the GNU readline library is available, it
can be used.

If Perl5 is installed, FvwmConsoleC.pl can be used as a command editor.
This can be accomplished by either copying FvwmConsoleC.pl to fvwmlib
directory as FvwmConsoleC or invoking FvwmConsole with -e option. For
example:

::

  Module FvwmConsole -e FvwmConsoleC.pl

If neither one is installed, a simple input reading function which
doesn\'t have editing capabilities is used.

GNU readline and FvwmConsoleC.pl have some frequent used commands in
common as default. These commands are similar to emacs. For more
details, refer GNU readline man and info pages, and FvwmConsoleC.pl man
page.

::

    Ctrl-A - beginning of line
    Ctrl-B - previous char
    Ctrl-D - delete char
    Ctrl-E - end of line
    Ctrl-F - next char
    Ctrl-H - backspace
    Ctrl-K - erase to the end of line
    Ctrl-N - next line
    Ctrl-P - previous line
    Ctrl-R - search reverse
    Ctrl-U - delete line
    Meta-B - previous word
    Meta-F - next word
    Esc <  - beginning of history
    Esc >  - end of history


EXITING
-------

FvwmConsole can be stopped by entering the EOF character (usually
CTRL-D).

**Note!** Do not use the "quit" command, as this is an fvwm builtin:
typing "quit" at the FvwmConsole command line will cause fvwm to exit.

SEE ALSO
--------

*xterm*\ (1), *FvwmConsoleC.pl*\ (1), GNU Readline library

AUTHOR
------

FvwmConsole is the original work of Toshi Isogai.
