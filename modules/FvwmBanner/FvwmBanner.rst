========================================================================
FvwmBanner
========================================================================

------------------------------------------------------------------------
the Fvwm Banner module
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

Module FvwmBanner

*FvwmBanner* can only be invoked by fvwm. Command line invocation of the
*FvwmBanner* module will not work.

DESCRIPTION
-----------

FvwmBanner displays an Fvwm Logo in the center of the screen for 3
seconds.

COPYRIGHTS
----------

None.

INITIALIZATION
--------------

Nothing interesting.

INVOCATION
----------

FvwmBanner can be invoked by the command \'Module FvwmBanner\'. This can
be bound to a menu or key-stroke in the .fvwm2rc file, but more likely
you would do this in the StartFunction or InitFunction, for example:

::

    AddToFunc InitFunction "I" Module FvwmBanner

You can also give it an optional file parameter, like \'FvwmBanner
doomface.xpm\' or specify an alternate default pixmap via configuration
options (see "\*FvwmBanner: Pixmap" below). Fvwm will search the
ImagePath to find the image, or you can use the full path to the image.

CONFIGURATION OPTIONS
---------------------

\*FvwmBanner: NoDecor
        Tells FvwmBanner to create a window that Fvwm will not manage and not
        decorate.

\*FvwmBanner: Pixmap *file*
        Tells FvwmBanner to display *file* instead of the built in pixmap.

\*FvwmBanner: Timeout *sec*
        Tells FvwmBanner to display for *sec* seconds instead of default of 3
        seconds.

AUTHOR
------

Robert Nation
