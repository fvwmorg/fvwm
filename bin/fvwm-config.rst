========================================================================
fvwm-config
========================================================================

------------------------------------------------------------------------
query an existing fvwm installation
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

**fvwm-config** [*--help*] [*--version*] [*--info*] [*--prefix*]
[*--exec-prefix*] [*--bindir*] [*--datadir*] [*--libexecdir*]
[*--sysconfdir*] [*--mandir*] [*--localedir*] [*--fvwm-moduledir*]
[*--fvwm-datadir*] [*--fvwm-perllibdir*] [*--default-imagepath*]
[*--default-userdir*] [*--fvwm-exe*] [*--supports*]
[*--supports-<feature>*]

DESCRIPTION
-----------

**fvwm-config** is a shell script that provides an information about the
fvwm version, installation directories, built-in paths and supported
features.

OPTIONS
-------

**fvwm-config** prints to the standard output in all options. Both short
and long GNU-like option names may be used. 

**-h --help -?**
  prints the short usage

**-v --version -V**
  prints the version

**-i --info**
  prints the full info page

**-P --prefix**
  prints the installation prefix

**-E --exec-prefix**
  prints the installation exec-prefix

**-B --bindir**
  prints the installation bindir

**-D --datadir**
  prints the installation datadir

**-L --libexecdir**
  prints the installation libexecdir

**-S --sysconfdir**
  prints the installation sysconfdir

**-M --mandir**
  prints the installation mandir

**-O --localedir**
  prints the installation localedir

**-m --fvwm-moduledir**
  prints FVWM\_MODULEDIR, where the modules are installed

**-d --fvwm-datadir**
  prints FVWM\_DATADIR, where the system wide configs are installed

**-p --fvwm-perllibdir**
  prints FVWM\_PERLLIBDIR, where the perl library is installed

**-I --default-imagepath**
  prints the built-in ImagePath

**-U --default-userdir**
  prints the default FVWM\_USERDIR, note: $HOME is not expanded

**-e --fvwm-exe**
  prints the fvwm executable name (in bindir)

**-s --supports**
  lists all supported features, one per line

**--supports-**\ *<feature>*
  prints nothing, returns: 0 if the *<feature>* is supported, 100 if not,
  200 if unknown. All or supported feature names may be found using
  *--info* or *--supports* respectively.

USAGE
-----

Here are some real life usages.

  Checks for xft support:

  ::

      if fvwm-config --supports-xft;
      then echo 1; else echo 0; fi

  *fvwm-themes* package checks for the correct *fvwm* version installed
  using:

  ::

      fvwm-config --version

  and tries to use the same installation directories:

  ::

      fvwm-config --bindir --mandir --fvwm-datadir

  A way to find the full path to the fvwm executable:

  ::

      echo 'fvwm-config --bindir'/'fvwm-config --fvwm-exe'

  A way to start modules in perl:

  ::

      use lib 'fvwm-config -p | tr -d '0';
      use FVWM::Module;

  For a more human readable output, try:

  ::

      fvwm-config --info

COPYING
-------

**fvwm-config** is a part of fvwm package and distributed by the same
terms, see GNU GPL.

AUTHOR
------

Mikhael Goikhman <migo@homemail.com>
