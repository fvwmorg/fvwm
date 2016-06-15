========================================================================
FvwmEvent
========================================================================

------------------------------------------------------------------------
the fvwm event module
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

*FvwmEvent* is a more versatile replacement for *FvwmAudio*. It can in
general be used to hook any *fvwm* function or program to any window
manager event. E.g: Delete unwanted Netscape Pop ups or application
error pop ups as they appear, play sounds, log events to a file and the
like. Be creative, you\'ll find a use for it.

*FvwmEvent* is spawned by *fvwm*, so no command line invocation will
work. From within the *.fvwm2rc* file, *FvwmEvent* is spawned as
follows:

Module FvwmEvent

or from within an *fvwm* pop-up menu:

::

  DestroyMenu Module-Popup
  AddToMenu   Module-Popup "Modules" Title
  + "Event"          Module FvwmEvent
  + "Auto"           Module FvwmAuto 200
  + "Buttons"        Module FvwmButtons
  + "Console"        Module FvwmConsole
  + "Ident"          Module FvwmIdent
  + "Banner"         Module FvwmBanner
  + "Pager"          Module FvwmPager 0 3

DESCRIPTION
-----------

The *FvwmEvent* module communicates with the *fvwm* window manager to
bind *actions* to window manager *events*. Different actions may be
assigned to distinct window manager events.

*FvwmEvent* can be used to bind sound files to events like *FvwmAudio*
(RiP) did. It can be used for logging event traces to a log file, while
debugging *fvwm*.

*FvwmEvent* can also have builtin support for the rplay library.
(heritage of FvwmAudio)

INVOCATION
----------

The invocation method was shown in the synopsis section. No command line
invocation is possible. *FvwmEvent* must be invoked by the *fvwm* window
manager. *FvwmEvent* accepts a single argument:

\-audio
  Enables FvwmAudio compatibility mode.

alias
  Makes FvwmEvent use *alias* as its name. This affects which lines from
  the user\'s configuration file are used.

Invoking FvwmEvent as *FvwmAudio* (either by using an alias or creating
a symlink) enables FvwmAudio compatibility mode.

CONFIGURATION OPTIONS
---------------------

*FvwmEvent* gets config info from **fvwm**\ \'s module configuration
database (see *fvwm*\ (1), section **MODULE COMMANDS**), and looks for
certain configuration options:

\*FvwmEvent: Cmd *command*
  This determines the *fvwm* function that is to be called with the event
  parameters. You might want to do one of the following (details below):
  
  ::
  
    # play sounds
    *FvwmEvent: Cmd builtin-rplay
    
    # execute distinct fvwm functions
    *FvwmEvent: Cmd
    
    # execute distinct external programs
    *FvwmEvent: Cmd exec

  This version of *FvwmEvent* has builtin *rplay* support which does not
  need to invoke an external audio player to play sounds. The rplay
  support is enabled when *FvwmEvent* is compiled with *HAVE\_RPLAY*
  defined and when *FvwmEvent: Cmd* is set to *builtin-rplay*. See remarks
  below if *FvwmEvent* is invoked in FvwmAudio compatibility mode.

  For example:
  
  ::
  
    *FvwmEvent: Cmd *builtin-rplay*
    *FvwmEvent: add_window drip.au

  rplay can be obtained via anonymous ftp at
  
  ::
  
    <URL:ftp://ftp.sdsu.edu/pub/rplay> or
    <URL:ftp://ftp.x.org/contrib/Event/audio/rplay>

  *FvwmEvent* also has support for any other external program. e.g: the
  rsynth \'say\' command:
  
  ::
  
    *FvwmEvent: Cmd "Exec /rsynth/say"
    *FvwmEvent: destroy_window "window closed"

  You can also use *fvwm*\ \'s builtin *Echo* command as *FvwmEvent: Cmd*
  to obtain debug output for *fvwm* events quietly. I used this setup to
  debug FvwmAuto:
  
  ::
  
    *FvwmEvent: Cmd *Echo*
    *FvwmEvent: focus_change "focus change"
    *FvwmEvent: raise_window "raise window"

  You can even call different shell commands for each event just by
  setting
  
  ::
  
    *FvwmEvent: Cmd exec
    *FvwmEvent: add_window 'killname "APPL ERROR"'

\*FvwmEvent: PassId
  Specifies that the event action will have an ID parameter added to the
  end of the command line. Most events will have the windowID of the
  window that the event refers to, new\_desk will have the new desk
  number. The windowID is a hexadecimal string preceded by 0x, desk
  numbers are decimal.

\*FvwmEvent: *window-manager-event action-or-filename*
    Binds particular actions to window manager events.

    e.g. for audio-events:
    
    ::
    
      *FvwmEvent: startup TaDa.au
      *FvwmEvent: shutdown Elvis_Left.au
      *FvwmEvent: unknown doh.au
      
      *FvwmEvent: new_page beam_trek.au
      *FvwmEvent: new_desk beam_trek.au
      *FvwmEvent: old_add_window drip.au
      *FvwmEvent: raise_window swoosh.au
      *FvwmEvent: lower_window swoosh.au
      *FvwmEvent: old_configure_window hammer.au
      *FvwmEvent: focus_change boing.au
      *FvwmEvent: enter_window boing.au
      *FvwmEvent: leave_window boing.au
      *FvwmEvent: destroy_window explosion.au
      *FvwmEvent: iconify ploop.au
      *FvwmEvent: deiconify ploop.au
      *FvwmEvent: window_name huh.au
      *FvwmEvent: icon_name beep.au
      *FvwmEvent: visible_icon_name beep.au
      *FvwmEvent: res_class beep.au
      *FvwmEvent: res_name beep.au
      *FvwmEvent: end_windowlist twang.au
      
      *FvwmEvent: icon_location beep.au
      *FvwmEvent: map beep.au
      *FvwmEvent: error beep.au
      *FvwmEvent: config_info beep.au
      *FvwmEvent: end_config_info beep.au
      *FvwmEvent: icon_file beep.au
      *FvwmEvent: default_icon beep.au
      *FvwmEvent: string plapper.au
      *FvwmEvent: mini_icon beep.au
      *FvwmEvent: windowshade beep.au
      *FvwmEvent: dewindowshade beep.au
      
      *FvwmEvent: visible_name beep.au
      *FvwmEvent: sendconfig beep.au
      *FvwmEvent: restack beep.au
      *FvwmEvent: add_window beep.au
      *FvwmEvent: configure_window beep.au
      
      *FvwmEvent: visible_icon_name beep.au
      *FvwmEvent: enter_window beep.au
      *FvwmEvent: leave_window beep.au
      *FvwmEvent: property_change beep.au

  The window related event handlers are executed within a window context.
  Previously PassId was used for this purpose, but now using PassId is not
  needed.

  Note: The enter\_window event is generated when the pointer enters a
  window. With the -passid option, that window\'s id is passed to fvwm. An
  enter\_window event is generated too when the pointer leaves a window
  and moves into the root window. In this case, the id passed is 0.

  Note: When the shutdown event arrives, FvwmEvent may be killed before it
  can trigger the associated action.

  Provided *fvwm* supports it (not yet), there\'s an additional event to
  replace all *fvwm* beeps with a sound:
  
  ::
  
    *FvwmEvent: beep beep.au

\*FvwmEvent: Delay *5*
  Specifies that an event-action will only be executed if it occurs at
  least 5 seconds after the previous event. Events that occur during the
  delay period are ignored. This option is useful if you don\'t want
  several sounds playing at the same time. The default delay is 0 which
  disables the Event delay.

\*FvwmEvent: StartDelay *delay*
  Specifies that an event-action will only be executed if it occurs at
  least *delay* seconds after the startup event. Events that occur during
  the delay period are ignored. This option is useful when *fvwm* starts
  and restarts using an audio player. The default delay is 0.

RPLAY OPTIONS
-------------

The following options are only valid with builtin rplay support. i.e:
when *FvwmEvent* was compiled with *HAVE\_RPLAY* defined. They are
used only if *FvwmEvent: Cmd* is set to *builtin-rplay*.

\*FvwmEvent: RplayHost *hostname*
  Specifies what host the rplay sounds will play on. The *hostname* can
  also be an environment variable such as $HOSTDISPLAY.

\*FvwmEvent: RplayPriority *0*
  Specifies what priority will be assigned to the rplay sounds when they
  are played.

\*FvwmEvent: RplayVolume *127*
  Specifies what volume will be assigned to the sounds when they are
  played.

FvwmAudio Compatibility Mode
----------------------------

When invoked in FvwmAudio compatibility mode (see above), FvwmEvent
accepts the following options to provide backwards compatibility for
FvwmAudio:

\*FvwmEvent: PlayCmd *command*
  This is equivalent to using \*FvwmEvent: Cmd to Exec commands. This
  determines the independent audio player program that will actually play
  the sounds. If the play command is set to *builtin-rplay* then the
  builtin rplay support will be used.

\*FvwmAudio: Dir *directory*
  Specifies the directory to look for the audio files. This option is
  ignored when rplay is used.

BUGS
----

It\'s REALLY noisy when *fvwm* starts and restarts using an audio player.
You can use FvwmEvent: StartDelay to fix this problem.

COPYRIGHTS
----------

This module has evolved of *FvwmAudio*, which in term is heavily based
on a similar Fvwm module called *FvwmSound* by Mark Boyns. *FvwmAudio*
simply took Mark\'s original program and extended it to make it generic
enough to work with any audio player. Due to different requests to do
specific things on specific events, *FvwmEvent* took this one step
further and now calls any *fvwm* function, or builtin-rplay. If
*fvwm*\ \'s Exec function is used, any external program can be called
with any parameter.

The concept for interfacing this module to the Window Manager, is
original work by Robert Nation.

Copyright 1998 Albrecht Kadlec. Copyright 1994, Mark Boyns and Mark
Scott. No guarantees or warranties or anything are provided or implied
in any way whatsoever. Use this program at your own risk. Permission to
use and modify this program for any purpose is given, as long as the
copyright is kept intact.

AUTHORS
-------

1994 FvwmSound Mark Boyns (*boyns@sdsu.edu*)

1994 FvwmAudio Mark Scott (*mscott@mcd.mot.com*)

1996 FvwmAudio Albrecht Kadlec

1998 FvwmEvent Albrecht Kadlec (*albrecht@auto.tuwien.ac.at*)
