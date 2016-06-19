========================================================================
fvwm-menu-headlines
========================================================================

------------------------------------------------------------------------
builds headlines menu definition for fvwm
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

SYNOPSIS
--------

**fvwm-menu-headlines** [ **\-\-help**\ \|\ **\-h**\ \|\ **\-?** ] [
**\-\-version**\ \|\ **\-V** ] [ **\-\-info** [site] ] [
**\-\-site**\ \|\ **\-s** site ] [ **\-\-name**\ \|\ **\-n** name ] [
**\-\-title**\ \|\ **\-t** title ] [ **\-\-item** item ] [
**\-\-exec**\ \|\ **\-e** exec-command ] [ **\-\-command**\ \|\ **\-e**
fvwm-command ] [ **\-\-icon\-title** icon ] [ **\-\-icon\-item** icon ] [
**\-\-icon\-home** icon ] [ **\-\-icon\-error** icon ] [ **\-\-wm\-icons** ] [
**\-\-frontpage** [where] ] [ **\-\-proxy**\ \|\ **\-p** host:port ] [
**\-\-file** [file] ] [ **\-\-fake** [file] ] [ **\-\-timeout** seconds ]

DESCRIPTION
-----------

This configurable perl script builds an fvwm menu definition for
headlines of popular news web sites: FreshMeat, Slashdot, LinuxToday,
DaemonNews, GNOME-News, KDE-News, RootPrompt, LinuxFr, ThinkGeek, CNN ,
BBC and more.

It is possible to specify a customized menu item format, change a
command (usually launching a browser) and add menu icons (there is a
support for the wm-icons package).

OPTIONS
-------

**\-\-help**
    show the help and exit

**\-\-version**
    show the version and exit

**\-\-info** [site]
    if site name is given print the site specific info, otherwise print all
    site names

**\-\-site** site
    defile a web site, headlines of which to show, this option also can be
    used together with \-\-help to get new defaults. Default site: freshmeat.

**\-\-name** name
    define menu name (default is "MenuHeadlinesFreshmeat")

**\-\-title** title
    define menu title (default is "Freshmeat Headlines").

**\-\-item** label-format | **\-\-exec** command-format
    define format for menu item or command (what is shown and what is
    executed when the item is chosen). Default label is \'%h\\t%[(%Y\-%m\-%d
    ``%H:``\ %M)]\'. TAB can be specified as \'\\t\', but in .fvwm2rc you
    should specify a double backslash or a real TAB .

    Format specifiers for a headline format:

    ::

        %h - headline
        %u - url
        %d - date in the native format (that site backend supplied)
        %[strftime-argument-string] - date/time, see strftime(3)
            the date/time is represented according to the local time;
            date and/or time fields that can't be guessed are stripped
            
            Example: %[|%d %B %Y| %H:%M %S]
                If site supplied only date - this becomes %[|%d %B %Y|],
                if site supplied no date - this becomes an empty string.
          
        %{name} - site specific named value, like %{comments}
        %(text) - arbitrary text, good for escaping or aligning

    These specifiers can receive an optional integer size, positive for
    right adjusted string or negative for left adjusted, example: ``%8x``;
    and optional \*num or \*\-num, which means to leave only the first or
    last (if minus) num of chars, the num must be greater than 3, since the
    striped part is replaced with "...", example: %\*30x. Both can be
    combined: %\-10\*\-20x, this instructs to get only the 20 last characters,
    but if the length is less then 10 \- to fill with up to 10 spaces on the
    right.

    Example:

    ::

          --exec "iceweasel -remote 'openURL(%u, new-window)' || iceweasel '%u'"

**\-\-command** command-format
    like **\-\-exec** above, but enables to specify any fvwm command, for
    example, "Function FuncFvwmShowURL \'%u\'" not only Exec.

    In fact, \-\-exec="mozilla \'%u\'" is equivalent to \-\-command="Exec mozilla
    \'%u\'"

**\-\-icon\-title** icon | **\-\-icon\-item** icon | **\-\-icon\-home** icon | **\-\-icon\-error** icon
    define menu icon for title, regular item, frontpage item and error item
    respectively. Default is no menu icons (equivalent to an empty icon
    argument).

**\-\-wm\-icons**
    define icon names suitable for use with wm-icons package. Currently this
    is equivalent to: \-\-icon\-title \'\' \-\-icon\-item menu/information.xpm
    \-\-icon\-home menu/home.xpm \-\-icon\-error menu/choice\-no.xpm.

**\-\-frontpage** [where]
    add the site frontpage item to the menu. Optional value can be used to
    specify where this item will be placed in the menu \- \'top\' or \'t\',
    \'bottom\' or \'b\'.

**\-\-proxy** host[:port]
    define a proxy to use. Example: \-\-proxy proxy.inter.net:3128

**\-\-file** [file]
    write the menu output to specified file. If no filename is given with
    this option (or empty filename), the default filename WORK\_HOME/SITE
    .menu is used. Without this option or with \'\-\' filename, the menu output
    is written to standard output.

**\-\-fake** [file]
    don\'t connect to the host using HTTP protocol, instead, read from
    WORK\_HOME/SITE .in file. The following reads input from freshmeat.in
    (downloaded http://freshmeat.net/backend/recentnews.txt) and saves
    output to segfault.menu (both files are in WORK\_HOME ):
    fvwm-menu-headlines \-\-site freshmeat \-\-fake \-\-file

**\-\-timeout** seconds
    limit a line reading from a socket to this timeout, the default timeout
    is 20 seconds.

    WORK\_HOME of this script is ~/.fvwm/.fvwm\-menu\-headlines. It is created
    if needed.

Option parameters can be specified either using \'=\' or in the next
argument. Short options are ok if not ambiguous: ``"\-h"``, ``"\-t"``; but
be careful with short options, what is now unambiguous, can become
ambiguous in the next versions.

USAGE
-----

1. One of the ways to use this script is to define a crontab entry to
run the script every hour or so for every monitored site:

::

      0,30 * * * * fvwm-menu-headlines --file --site freshmeat
      1,31 * * * * fvwm-menu-headlines --file --site linuxtoday
      2,32 * * * * fvwm-menu-headlines --file --site slashdot

Then add these lines to your fvwm configuration file:

::

      DestroyFunc FuncFvwmMenuHeadlines
      AddToFunc   FuncFvwmMenuHeadlines
      + I Read "$HOME/.fvwm/.fvwm\-menu-headlines/$0.menu"
      
      DestroyMenu MenuHeadlines
      AddToMenu   MenuHeadlines "Headlines" Title
      + MissingSubmenuFunction FuncFvwmMenuHeadlines
      + "FreshMeat"  Popup freshmeat
      + "LinuxToday" Popup linuxtoday
      + "Slashdot"   Popup slashdot

2. Another way to use this script (only if you have fast network/proxy)
is to run it every time you want to open your Headlines submenus. (Note,
the submenu that is once created is not reloaded, use "Reset all".)

In this case your fvwm configuration lines could be:

::

      DestroyFunc FuncFvwmMenuHeadlines
      AddToFunc   FuncFvwmMenuHeadlines
      + I PipeRead "fvwm-menu-headlines --site $0"
      #+ I Schedule 900000 DestroyMenu $0  # reset generated menu in 15 minutes
      
      DestroyMenu MenuHeadlines
      AddToMenu   MenuHeadlines "Headlines" Title
      + MissingSubmenuFunction FuncFvwmMenuHeadlines
      + "FreshMeat"  Popup freshmeat
      + "Slashdot"   Popup slashdot
      + "LinuxToday" Popup linuxtoday
      + "GNOME News" Popup gnome-news
      + "KDE News"   Popup kde-news
      + "" Nop
      + "Reset all"  FuncResetHeadlines
      
      DestroyFunc FuncResetHeadlines
      AddToFunc   FuncResetHeadlines
      + I DestroyMenu freshmeat
      + I DestroyMenu linuxtoday
      + I DestroyMenu slashdot
      + I DestroyMenu gnome-news
      + I DestroyMenu kde-news

And finally, add "Popup MenuHeadlines" somewhere.

3. Here is a usual usage. Use FvwmConsole or FvwmCommand to run fvwm
commands from a shell script. Every time you want headlines from some
site, execute (give any additional options if you want):

::

    PipeRead "fvwm-menu-headlines --site newsforge --name MenuHeadlinesNewsForge"
    # this may take several seconds, you may use: BusyCursor Read true
    Popup MenuHeadlinesNewsForge

HOW TO ADD SITE HEADLINES
-------------------------

It is possible to add user defined site headlines without touching the
script itself. Put your perl extensions to the file
WORK\_HOME/extension.pl. For each site add something similar to:

::

    $site_info->{'myslashdot'} = {
        'name' => "MySlashdot",
        'host' => "myslashdot.org",
        'path' => "/myslashdot.xml",
        'func' => \&process_my_slashdot,
        # the following string is only used in --info
        'flds' => 'time, title, department, topic, author, url',
    };
    sub process_my_slashdot () {
        return process_xml(
            'story',
            # mandatory 'h', 'u' and 'd' aliases or undef
            { 'h' => 'title', 'u' => 'url', 'd' => 'time' },
            sub ($) {  # convert 'd' string to (y, m, d, H, M, S)
                $_[0] =~ /(\d+)-(\d+)-(\d+) (\d+):(\d+):(\d+)/;
                ($1, ($2 || 0) - 1, $3, $4, $5, $6);
            }, +0,  # timezone offset; already in UTC
        );
    }
    1;

AUTHORS
-------

This script is inspired by WMHeadlines v1.3 by:

Jeff Meininger <jeffm@boxybutgood.com>
(http://rive.boxybutgood.com/WMHeadlines/).

Reimplemented for fvwm and heavily enhanced by:

Mikhael Goikhman <migo@homemail.com>, 16 Dec 1999.

COPYING
-------

The script is distributed by the same terms as fvwm itself. See GNU
General Public License for details.

BUGS
----

I try to keep all supported site info up to date, but sites often go
down, change their backend formats, change their httpd responses, just
stop to post news and so on; the script in the latest cvs may be more up
to date.

The headline times may be off by one hour or more, since the time is
displayed for your local time zone, and the time zone of the original
time in the site backend output is often guessed (sometimes
incorrectly); similarly it is guessed whether to apply the daylight
saving correction.

Report bugs to fvwm\-bug@fvwm.org.
