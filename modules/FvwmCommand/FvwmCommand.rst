========================================================================
FvwmCommand
========================================================================

------------------------------------------------------------------------
fvwm command external interface
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

FvwmCommand [-cmrvw] [-S name] [-i level] [-f name] [-F level]
[command...]

DESCRIPTION
-----------

FvwmCommand lets you monitor fvwm transaction and issue fvwm command
from a shell command line or scripts. FvwmCommand takes each argument as
a fvwm command. Quotes can be used to send commands including spaces.

::

    FvwmCommand 'FvwmPager 0 1'

INVOCATION
----------

FvwmCommandS should be spawned once by fvwm, either in .fvwm2rc file,
from menu, or from FvwmConsole. From then on, FvwmCommand can be called
from a shell or script to execute fvwm commands.

From within .fvwm2rc file:

::

    Module FvwmCommandS

    or

::

    AddToFunc StartFunction "I" Module FvwmCommandS

Then, in script file or from shell:

::

    FvwmCommand  'popup Utilities'

OPTIONS
-------

*-c*
    Informs FvwmCommand to read multiple commands from the standard input
    instead of the one command specified in the command line arguments.
    This disables *-m* or *-i*.

    ::

        (echo "Exec xload"; echo "Beep") | FvwmCommand -c

*-F <level>*
    Specifies the level of fvwm window flags FvwmCommand outputs.
    
    0
        No window flags will be printed.

    2
        Full window flags will be printed if information level, -i option, is 2 or 3.


*-f <name>*
    Specifies an alternative FIFO set to communicate with a server. The
    default FIFO set is /var/tmp/FvwmCommand-${DISPLAY}C, in which
    FvwmCommand..C is used to send commands and FvwmCommand..M is to receive
    messages. If that path is unusable
    ${FVWM\_USERDIR}/FvwmCommand-${DISPLAY} will be used instead.
    FvwmCommandS must have been invoked with the same <name> as its first
    argument prior to FvwmCommand invocation. Alternatively, option -S can
    be used. Refer option -S. This option -f is useful when a dedicated
    connection is necessary to run a background job while another connection
    is kept for interactive use.

*-i <level>*
    Specifies the level of information that FvwmCommand outputs.

    0
        Error messages only.

        ::

            FvwmCommand -i0 FvwmBanner

        will show a banner without any output. On the other hand,

        ::

            FvwmCommand -i 0 foobar

        will return,

        ::

            [fvwm][executeModule]: <<ERROR>> No such module
            ´foobar´ in ModulePath '/usr/lib/X11/fvwm'

        Note that Fvwm doesn\'t return any error messages in cases like below
        since \'windowid\' itself is a valid command.

        ::

            FvwmCommand -i 0 'windowid foo bar'

    1
        Errors, replies and window configuration information. This is the default.

        ::

            FvwmCommand send_windowlist

        Information like below will show up.

        ::

            0x02000014 window               FvwmConsole
            0x02000014 icon                 FvwmConsole
            0x02000014 class                XTerm
            0x02000014 resource             FvwmConsole
            0x01c00014 window               console
            0x01c00014 icon                 console
            0x01c00014 class                XTerm
            0x01c00014 resource             console
            0x01000003 window               Fvwm Pager
            0x01000003 icon
            0x01000003 class                FvwmModule
            0x01000003 resource             FvwmPager
            0x00c0002c window               emacs: FvwmCommand.man
            0x00c0002c icon                 FvwmCommand.man
            0x00c0002c icon file            xemacs.xpm
            0x00c0002c class                Emacs
            0x00c0002c resource             emacs
            end windowlist

        The first column shows the window ID number, which can be used in
        \'windowid\' command. The second column shows the information types. The
        last column shows the information contents. If no information is
        returned, add -w <time> or -r option. This might be needed in heavily
        loaded systems.

    2
        Above and static window information.

        ::

            FvwmCommand -i2 'FvwmPager 0 1'

        The below is its output.

        ::

            0x03c00003 frame                x 962, y 743, width 187, height 114
            0x03c00003 desktop              0
            0x03c00003 StartIconic          no
            0x03c00003 OnTop                yes
            0x03c00003 Sticky               yes
            0x03c00003 WindowListSkip       yes
            0x03c00003 SuppressIcon         no
            0x03c00003 NoiconTitle          no
            0x03c00003 Lenience             no
            0x03c00003 StickyIcon           no
            0x03c00003 CirculateSkipIcon    no
            0x03c00003 CirculateSkip        no
            0x03c00003 ClickToFocus         no
            0x03c00003 SloppyFocus          no
            0x03c00003 SkipMapping          no
            0x03c00003 Handles              no
            0x03c00003 Title                no
            0x03c00003 Mapped               no
            0x03c00003 Iconified            no
            0x03c00003 Transient            no
            0x03c00003 Raised               no
            0x03c00003 Visible              no
            0x03c00003 IconOurs             no
            0x03c00003 PixmapOurs           no
            0x03c00003 ShapedIcon           no
            0x03c00003 Maximized            no
            0x03c00003 WmTakeFocus          no
            0x03c00003 WmDeleteWindow       yes
            0x03c00003 IconMoved            no
            0x03c00003 IconUnmapped         no
            0x03c00003 MapPending           no
            0x03c00003 HintOverride         yes
            0x03c00003 MWMButtons           no
            0x03c00003 MWMBorders           no
            0x03c00003 title height         0
            0x03c00003 border width         4
            0x03c00003 base size            width 8, height 7
            0x03c00003 size increment       width 9, height 9
            0x03c00003 min size             width 8, height 7
            0x03c00003 max size             width 32767, height 32767
            0x03c00003 gravity              SouthEast
            0x03c00003 pixel                text 0xffffff, back 0x7f7f7f
            0x03c00003 window               Fvwm Pager
            0x03c00003 icon                 Fvwm Pager
            0x03c00003 class                FvwmModule
            0x03c00003 resource             FvwmPager

    3
        All information available.

        ::

            FvwmCommand -i3 'Killmodule Fvwm*'

        This will report which windows are closed.

        ::

            0x03400003 destroy
            0x02400002 destroy

*-m*
    Monitors fvwm window information transaction. FvwmCommand continuously 
    outputs information that it receives without exiting. This option can 
    be used in a background job often combined with -i3 option in order 
    to control windows dynamically.                                               

    ::

        FvwmCommand -mi3 | grep 'iconify'

    It will report when windows are iconified or de-iconified.

    Note: FvwmCommand does not block buffer its output but many utilities
    such as grep or sed use block buffer. The output of the next example
    will not show up until either FvwmCommand is terminated or stdout buffer
    from grep is filled.

    ::

        FvwmCommand -mi3 | grep ' map' |
        sed 's/(0x[0-9a-f]*).*/windowid 1 move 0 0/'

    Instead, use tools with buffer control such as pty or perl. The below
    will iconify new windows when opened.

    ::

        Fvwm -mi3 | perl -ne '
        $|=1;
        print "windowid $1 iconify\n" if /^(0x\S+) add/;
        ´ > ~/.FvwmCommandC

*-r*
    Waits for a reply before it exits. FvwmCommand exits if no information 
    or error is returned in a fixed amount of time period. 
    (Refer option -w.) The option -r overrides this time limit and wait 
    for at least one message back. After the initial message, it will 
    wait for another message for the time limit. This option is useful 
    when the system is too loaded to make any prediction when the system 
    is responding AND the command causes some message to be sent back.                                                      

*-S <name>*
    Invokes another server, FvwmCommandS, with FIFO set <name>.
    
    If -f option is not used with this option, the invoking FvwmCommand
    uses the default FIFO to communicate the default server to invoke a
    new server.
    
    If -f option is used with this option, the invoking FvwmCommand uses
    the default FIFO to communicate the default server to invoke a new
    server. Then, switch the FIFO set and start communicating the new
    server.
    
    This option -S is useful when a dedicated connection is necessary to
    run a background job while another connection is kept for interactive
    use.

    If the <name> is a relative path name, that is relative from where fvwm
    is running, not from where FvwmCommand is invoked.

*-v*
    Returns FvwmCommand version number and exits.

*-w <time>*
    Waits for <time> micro seconds for a message. FvwmCommand exits if no
    information or error is returned in a fixed amount of time period unless
    option -m is used. The default is 500 ms. This option overrides this
    default value.

WRAPPER
-------

FvwmCommand.sh has bourne shell function definitions to keep the syntax
similar to fvwm configuration file. This file is to be sourced:

::

    . FvwmCommand.sh
    DesktopSize 5x5

FvwmCommand.pm is for perl in order to keep the syntax similar to fvwm
configuration file. Commas can be used to separate fvwm commands\'
arguments.

::

    use FvwmCommand;
    if ( $ARGV[0] eq 'home' ) {
        Desk 0,0; GotoPage '1 1';
    } elsif ( $ARGV[0] eq 'jump' ) {
        Desk "0 2"; GotoPage 0, 1;
    }

Although arguments in FvwmCommand are not case sensitive as fvwm, the
functions defined in FvwmCommand.sh and FvwmCommand.pl are case
sensitive.

ERRORS
------

If the following error message show up, it is most likely that
FvwmCommandS is not running.

::

    FvwmCommand error in opening message fifo
    --No such file or directory--

Fvwm modules don\'t return error messages to fvwm but output on stderr.
These error messages will not be shown as FvwmCommand messages.

FvwmCommand is an interface to send commands to and receive information
from Fvwm2 from processes which are not Fvwm modules.

EXAMPLES
--------

::

    test1.pl        - takes 1 argument 't' to invoke FvwmTalk 
                                       'td' to kill FvwmTalk 
                                       '' to move windows
    
    test2.sh        - takes 1 argument 'b' to invoke FvwmButtons 
                                       'kb' to kill FvwmButtons
                                       'r' to change # of button rows
                                       'c' to change # of button columns
    
    ex-auto.pl      - auto raise small windows. It will keep them visible.
    
    ex-cascade.pl   - cascade windows, then move them back.
    
    ex-grpmv.pl     - choose a group of windows to move together.

Above examples are not meant to be practical but to show how it can
be done.

focus-link.pl
    This is a user programmable window focus script.
    
    Default behavior is:

    1.  When a window is opened up, focus the window and move the pointer
        to it. The parent window regains focus when a window is closed.
        Parenthood is determined when a window is opened. It is the last
        focused window with the same X class.
    2.  #1 would not occur to AcroRead opening window.
    3.  #1 would not occur when SkipMapping is set and the window is the
        only window of its class.
    4.  For Netscape find dialog window, addition to #1, resize the window
        to 300x150 pixels and move it to East edge of the screen.
        Download/upload windows will not be focused nor be in focus link
        list.
    5.  Move appletviewer to NorthWest corner.
    6.  Xterm won\'t focus back to its parent after closed.
    7.  When a window is de-iconified, focus it and move the pointer.

focus-Netscape.pl
    Focuses pop-up windows, such as \'open URL\' or \'find\' whenever
    opened up. This let the user to type in immediately without
    moving mouse. This script also moves \'download\' window to the
    right edge to keep it visible. If this is invoked from
    .fvwm2rc, use as:

    ::
    
        AddToFunc "StartFunction" "I" Module FvwmCommandS
        + "I" Exec $HOME/scripts/focus-Netscape.pl

push-away.pl <direction> <window name>
    Pushes windows away to avoid overlapping. use as:

    ::
    
        push-away.pl up \'Fvwm Pager\'

SEE ALSO
--------

fvwm

AUTHOR
------

FvwmCommand is the original work of Toshi Isogai.
