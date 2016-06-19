========================================================================
FvwmScroll
========================================================================

------------------------------------------------------------------------
the fvwm scroll-bar module
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

FvwmScroll is spawned by fvwm, so no command line invocation will work.

DESCRIPTION
-----------

The FvwmScroll module prompts the user to select a target window, if the
module was not launched from within a window context in Fvwm. After
that, it adds scroll bars to the selected window, to reduce the total
desktop space consumed by the window.

FvwmScroll should not be used with windows which move or resize
themselves, nor should it be used with windows which set the
WM\_COLORMAP\_WINDOWS property. Operation is fine with windows that have
a private colormap.

COPYRIGHTS
----------

The FvwmScroll program, and the concept for interfacing this module to
the Window Manager, are all original work by Robert Nation.

Copyright 1994, Robert Nation. No guarantees or warranties or anything
are provided or implied in any way whatsoever. Use this program at your
own risk. Permission to use this program for any purpose is given, as
long as the copyright is kept intact.

INITIALIZATION
--------------

During initialization, *FvwmScroll* gets config info from **fvwm**\ \'s
module configuration database (see *fvwm*\ (1), section **MODULE
COMMANDS**) to determine which colors to use.

If the FvwmScroll executable is linked to another name, ie ln -s
FvwmScroll MoreScroll, then another module called MoreScroll can be
started, with a completely different configuration than FvwmScroll,
simply by changing the keyword FvwmScroll to MoreScroll.

INVOCATION
----------

FvwmScroll can be invoked by binding the action \'Module FvwmScroll x y\'
to a menu or key-stroke in the .fvwm2rc file. The parameter x and y are
either integers or integers immediately followed by a p, which describe
the horizontal and vertical size modification of the window. An integer
describe a size reduction. An integer followed by a p describe a size as
a percentage of the height or the width of a full screen but the size is
never larger than the original window size (0p will do nothing). Fvwm
will search directory specified in the ModulePath configuration option
to attempt to locate FvwmScroll. Although nothing keeps you from
launching FvwmScroll at start-up time, you probably don\'t want to.

CONFIGURATION OPTIONS
---------------------

\*FvwmScroll: Colorset *n*
  Tells the module to use colorset *n*. See FvwmTheme.

\*FvwmScroll: Back *color*
  Tells the module to use *color* instead of black for the window
  background. Switches off the Colorset option.

BUGS
----

When the scroll bars are removed by clicking on the button in the lower
right corner, the window does not restore its location correctly.

AUTHOR
------

Robert Nation
