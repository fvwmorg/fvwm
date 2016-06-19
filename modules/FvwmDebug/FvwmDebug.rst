========================================================================
FvwmDebug
========================================================================

------------------------------------------------------------------------
the fvwm module debugger
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

FvwmDebug should be spawned by *fvwm*\ (1) for normal functionality.

To run this module, place this command somewhere in the configuration:

::

        Module FvwmDebug [optional−params]

To stop this module, execute:

::

        KillModule FvwmDebug

DESCRIPTION
-----------

This module persistently dumps all fvwm event details and optionally
some other information into the standard error stream or a file, good
for debugging purposes. The output may be optionally redirected to
*xconsole* or similar window.

INVOCATION
----------

There are several command line switches:

**FvwmDebug** [ **−−args**\ \|\ **−−noargs** ] [
**−−events**\ \|\ **−−noevents** ] [ **−−log** *file* ] [ **−−xconsole**
] [ **−−mask** *mask* ] [ **−−xmask** *mask* ] [ **−−debug** *level* ] [
**−−track** *tracker-name* ] [ **−−send−configinfo** ] [
**−−send−windowlist** ]

Long switches may be abbreviated to shorter switches.

**−−noargs** − do not print all arguments of the event, just its name.
**−−args** is the default.

**−−noevents** − do not print even event names, implies **−−noargs**. It
is similar in effect to setting both **−−mask** and **−−xmask** to 0,
but the events are actually received by the module, they are just not
printed.

This option may be useful if **−−track** or/and **−−debug** is used.

The default is **−−events** normally, and **−−noevents** if one or more
**−−track** options specified.

**−l**\ \|\ **−−log** *file* − specify the log file name instead of the
standard error stream. If the log file can\'t be open for writing, the
default standard error stream is used.

The *file* may start with a pipe \'\|\', this is similar to the usual
meaning of a pipe, the output is piped to the specified command. See
also **−−xconsole** option.

**−xc**\ \|\ **−−xconsole** − this is a shortcut for:

::

        FvwmDebug −−log '|xconsole −file /dev/stdin −geometry 600x400 −notify'

That shows the module output in the *xconsole* window rather than the
standard error stream.

**−m**\ \|\ **−−mask** *mask* − set the module mask, 31 bit integer. By
default almost all events are monitored (except for some flood events
like *CONFIGURE\_WINDOW* or *FOCUS\_WINDOW* . The special value of *−1*
sets the maximal mask.

**−x**\ \|\ **−−xmask** *mask* − set the module extended mask, 31 bit
integer. By default almost all events are monitored (except for some
flood events like *ENTER\_WINDOW* or *LEAVE\_WINDOW* . The special value
of *−1* sets the maximal extended mask.

**−d**\ \|\ **−−debug** *level* − use the Perl library debugging
mechanism. The useful *level*\ s are 2 to 4.

**−t**\ \|\ **−−track** *tracker-name* − create the given Perl library
tracker and observe its main observable. This option may be specified
multiple times. This options implies **−−noevents** unless explicitly
overwritten. You may optionally try **−−debug**, for example:

::

        FvwmDebug −xc −−track PageInfo −−track GlobalConfig −−debug 3

Run "fvwm-perllib man" to get the names of all existing trackers in your
installed Perl library.

**−sc**\ \|\ **−−send−configinfo** − send **Send\_ConfigInfo** command
to *fvwm* on startup, this results in a lot of events received.

**−sw**\ \|\ **−−send−windowlist** − send **Send\_WindowList** command
to *fvwm* on startup, this results in a lot of events received.

SEE ALSO
--------

See also FvwmGtkDebug.

AUTHOR
------

Mikhael Goikhman <migo@homemail.com>.
