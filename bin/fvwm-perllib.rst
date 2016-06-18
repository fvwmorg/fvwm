========================================================================
fvwm-perllib
========================================================================

------------------------------------------------------------------------
shows the documentation of the Fvwm Perl library
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

**fvwm-perllib** [ **\-\-help**\ \|\ **\-h**\ \|\ **\-?** ] [
**\-\-version**\ \|\ **\-v**\ \|\ **\-V** ] [ **man** [ *Perl::Class* ] ] [
**cat** [ *Perl::Class* ] ] [ **raw** [ *Perl::Class* ] ] [ **dir** ]

DESCRIPTION
-----------

Starting from fvwm\-2.5.x versions there is a built-in support for
creating fvwm modules in Perl. This **fvwm-perllib** utility provides
help services for the Fvwm Perl library.

OPTIONS
-------

**\-\-help**
  show the help and exit

**\-\-version**
  show the version and exit

**\-\-man** or **man** [ *Perl::Class* ]
  show manual page just like *man*\ (1)

**\-\-cat** or **cat** [ *Perl::Class* ]
  show manual page in plain text

**\-\-raw** or **raw** [ *Perl::Class* ]
  generate output in man format (not human readable)

**\-\-dir** or **dir**
  print perllib directory without a trailing end of line

USAGE
-----

Use this in the fvwm modules written in Perl:

::

        use lib `fvwm-perllib dir`;

Introduction to the Fvwm Perl library:

::

        % fvwm-perllib man

Manual page for the ``"FVWM::Module"`` class:

::

        % fvwm-perllib man FVWM::Module

Standard options:

::

        % fvwm-perllib --help
        % fvwm-perllib --version

AUTHORS
-------

Mikhael Goikhman <migo@homemail.com>.

COPYING
-------

The script is distributed by the same terms as fvwm itself. See GNU
General Public License for details.

BUGS
----

No known bugs.

Report bugs to fvwm\-bug@fvwm.org.
