FVWM
----

[![Build Status](https://travis-ci.org/fvwmorg/fvwm.svg?branch=master)](https://travis-ci.org/fvwmorg/fvwm)

------------------------------------------------------------------------------

**Please note that FVWM2 is in maintenance mode.  This means it won't be
receiving any new features.  Bug fixes will be to the core of FVWM2 only.  Any
problems found in modules will be to fix segfaults only.**

**All users are hereforth encouraged to use [fvwm3](https://github.com/fvwmorg/fvwm3), and to report any bugs.**

**The rest of this README and associated documentation for FVWM is for
historical purposes only.**

------------------------------------------------------------------------------

Welcome to fvwm.  Fvwm is a multiple large virtual desktop window manager,
originally (a looooong time ago!) derived from twm.

Fvwm is intended to have a small memory footprint but a rich feature set, be
extremely customizable and extendible, and have a high degree of Motif mwm
compatibility.

**ALL VERSIONS OF FVWM PRIOR TO 2.6.X ARE NOT SUPPORTED UPSTREAM.**

Users of fvwm prior to 2.6.X can make use of the
[fvwm-convert-2.6 utility](./bin/fvwm-convert-2.6.in) to try and have their
configuration file converted to a newer syntax.  Please see its manpage for
more details on how to use it.

Releases
--------

* Latest stable release: [2.6.7](https://github.com/fvwmorg/fvwm/releases/tag/2.6.7)
* Long-term stable release: [fvwm2-stable](https://github.com/fvwmorg/fvwm/archive/fvwm2-stable.zip)

The **Long-term stable release** represents the fvwm version prior to 2.6.7
which contains ported bug-fixes from 2.6.7, but retains the modules and other
features removed in 2.6.7.  This version **won't** receive any new features but
may occsaionally receive bug-fixes.

Installation
------------

See [the installation instructions](./INSTALL.md)

Development
-----------

Those interested in contributing to FVWM should have [a read of the developer
documentation](./docs/DEVELOPERS.md).

A [TODO file](./TODO.md) exists, and sometimes even things from it are worked
on.

Comments, Questions?
--------------------

There is the `#fvwm` IRC channel on `freenode.net` which you can use to chat
to people about FVWM.

If you have any questions, concerns, bug reports, enhancement requests,
etc., please feel free to send an email to the fvwm mailing list, or open a
Github issue.

Have fun!

-- The fvwm-workers
