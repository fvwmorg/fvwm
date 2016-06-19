========================================================================
fvwm-convert-2.2
========================================================================

------------------------------------------------------------------------
convert fvwm 1.xx configuration file to fvwm 2.xx
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

style

SYNOPSIS
--------

**fvwm-convert-2.2** [*source*] [*dest*]

DESCRIPTION
-----------

**fvwm-convert-2.2** is a simple program that tries to convert an fvwm
1.xx configuration file into an fvwm 2.xx compatible format. It is not
perfect, especially with regards to Mouse and Key commands, but it
provides a basically-working *.fvwm2rc* file which can be further
modified at leisure.

By default, the program will convert *~/.fvwmrc*, saving the results in
*~/.fvwm2rc*. Different source and destination files may be given, with
a destination of \'-\' meaning standard output. If the destination file
already exists, it will be backed up first to *~/.fvwm2rc.bak* (with
whatever the destination file is called replacing *~/.fvwm2rc*).

COMPATIBILITY
-------------

In the past this utility was called *fvwmrc\_convert*.

AUTHOR
------

This manual page was written by Julian Gilbey <jdg@debian.org>.
