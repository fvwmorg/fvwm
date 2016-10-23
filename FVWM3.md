FVWM3
======

Since fvwm3 is a clean-break from fvwm2.x, we have an opportunity to not worry
about maintaining backwards compatibility and write most of fvwm3 from
scratch.  Given the developments in libraries since fvwm2 was written, there's
a good chance we can use these right away.

Goals (high-level)
==================

* Minimal core -- fvwm3 should be functional without excessive third-party
  libraries, such as image libraries, etc.  Keeping the core as small as
  possible (but still being useful) means functionality that has to be in the
  core should be more justifiable.

* Modular design -- fvwm3 should allow for its functionality to be made up of
  separate modules which the user can choose to use at run-time.  These
  modules should be writeable in any language through an API.

* Scriptable -- fvwm3 should be scriptable, providing a CLI-style set of
  commands for controlling it (think how `cvs` or `git` command-line tools
  work).  This would allow for shell scripts or any language to use all commands
  of fvwm3.

* Configuration -- fvwm3 should store its configuration in such a way that it
  can be retrieved in the same way it was read in (so it can be dumped out again
  from a running instance of fvwm3).

* RandR support -- fvwm3 should handle multiple screens with ease.

X11 Features
============

* Use [XCB](https://xcb.freedesktop.org/) -- should reduce a lot of latency to
  the X11 server.

* Use [RandR](https://xcb.freedesktop.org/manual/group__XCB__RandR__API.html)

* Consider Wayland?  https://wayland.freedesktop.org/

Detail
======

Specific low-level details include:
