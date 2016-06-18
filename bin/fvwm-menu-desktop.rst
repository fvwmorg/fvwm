========================================================================
fvwm-menu-desktop
========================================================================

------------------------------------------------------------------------
Reads XDG menu files and creates Fvwm menus
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

fvwm-menu-desktop [ **−−help**\ \|\ **−h** ] [ **−−version**\ \|\ **−v**
] [ **−−install−prefix** *DIR* ] [ **−−desktop** *NAME* ] [
**−−menu−type** *NAME* ] [ **−−theme** *NAME* ] [
**−−with−titles**\ \|\ **−w** ] [ **−−enable−mini−icons** ] [
**−−size**\ \|\ **−s** *NUM* ] [ **−−mini−icon−dir**\ \|\ **−t** *DIR* ]
[ **−−title**\ \|\ **−t** *NAME* ] [ **−−insert−in−menu** *NAME* ] [
**−−get−menus** *all*\ \|\ *desktop* ] [ **−−set−menus** *menu\_paths* ]
[ **−−verbose** ]

DESCRIPTION
-----------

This is a python script which parses XDG menus definitions to build
corresponding fvwm menus.

OPTIONS
-------

Main Options

**−−help**
  Show the help and exit.

**−−version**
  Show the version and exit.

**−−install-prefix** *DIR*
  Optional parameter to override the standard locations for XDG menu
  definitions. The standard locations are /etc/xdg/menus (and
  $HOME/.config/menus if it exists).

**−−desktop** *NAME*
  Optional parameter to override the *NAME* of the main desktop
  environment installed on the system. If a system offers multiple desktop
  environments $XDG\_MENU\_PREFIX is typically set and is ignored if
  −−desktop is denoted. Possible names are: *gnome*, *kde*, *xfce*,
  *lxde*, *debian*, etc.

**−−menu−type** *NAME*
  Defines which type of menus should be found. Possible *NAME* types could
  be: *applications*, *settings*, *preferences*, etc.

  Note that if the specified menu type doesn\'t exist the generated menu is
  empty!

**−−theme** *NAME*
  Defines the used icon theme. Default is *gnome* but all others found in
  /usr/share/icons could be used except the *hicolor* theme because it\'s
  the default fallback theme if no icon is found.

**−−with−titles**\ \|\ **−w**
  If this option is set menus are generated with titles. Default is no
  titles.

**−−title**\ \|\ **−t** *NAME*
  Option to define the menu title *NAME* of the top menu used by Fvwm\'s
  **Popup** command. Default is "FvwmMenu".

**−−insert−in−menu** *NAME*
  Option to insert generated menu(s) **IN** a menu *NAME* (its top title).

  Note that this option does not work correctly with the Regnerate Menus
  menu entry in a normal built menu since items inserted into such a menu
  cannot be removed (currently). If you use this option there and want to
  update your menus, you have to restart fvwm. A better way is to use
  dynamic menus (see the example in the USAGE section).

**−−get−menus** *all*\ \|\ *desktop*
  Prints a space separated list of full menu paths. *all* is all menus on
  the system except empty ones. *desktop* is desktop related menus. No
  menu generation is done.

  This option is meant for use with the configuration tool.

**−−set−menus** *menu\_paths*
  Expects a space separated list of full menu paths to generate user
  specified menus

  This option is meant for use with the configuration tool.

**−−verbose**
  Enables additional information printouts on STDERR.

  Icons Options
    By default, fvwm-menu-desktop builds menus without mini−icons. To enable
    mini−icons use:

    **−−enable−mini−icons**
      This option enables mini−icons in the menus. If set, 24x24 mini-icons
      are used. If the specified icon isn\'t that size it will be converted if
      **ImageMagick** is installed and saved in $HOME/.fvwm/icons or to the
      directory specified with −−mini−icon−dir option. Otherwise no icon
      appears in the menu for that entry. With most distributions, all the
      menu entries will have mini-icons appropriate to the application.

    **−−size**\ \|\ **−s** *NUM*
      If −−enable−mini−icons is used the *size* of the icons can changed with
      this parameter. Default is 24.

    **−−mini−icon−dir** *DIR*
      When the right size mini-icon isn\'t available, fvwm-menu-desktop creates
      icons with the right size in $HOME/.fvwm/icons. If you don\'t want to use
      the default directory, $HOME/.fvwm/icons, use this option to specify a
      different folder.

USAGE
-----

Without any parameters **fvwm-menu-desktop** creates a menu named
"FvwmMenu" with sub menus found for the main desktop environment
installed on the system.

To add the default generated menu to the "Root" menu add the following
to your fvwm config file (~/.fvwm/config or ~/.fvwm/.fvwm2rc). This
generates the menu each time you pop it up:

  ::

      AddToMenu MenuRoot "XDG Menus" Popup FvwmMenu
      PipeRead 'fvwm-menu-desktop'

This is likely to be too slow and is not recommended.

Another possibility is to use **DynamicPopupAction**, the menu will be
built only if you pop up the menu. The following creates a "KDE Menus"
menu which contains all Kde menus found on the system which is built
only the first time you pop it up:

  ::

      AddToMenu MenuRoot "KDE Menus" Popup FvwmKde
       ...


      AddToMenu FvwmKde
      + DynamicPopupAction PipeRead 'fvwm-menu-desktop --desktop kde \
                                                       --title FvwmKde \
                                                       --enable-mini-icons \
                                                       [other options]'

The example above generates a menu with the Xdg menus as sub menus. If
the sub menus should appear one level higher do this:

  ::

      AddToMenu MenuRoot "Root Menu" Title
      + PipeRead 'fvwm-menu-desktop --insert-in-menu MenuRoot'

To generate single menus like *preferences*:

  ::

      fvwm-menu-desktop --desktop kde --menu-type preferences --title FvwmPref \
                        --enable-mini-icons -size 16 --with-titles

This generates a single KDE Preferences menu with top title "FvwmPref",
mini icons with a size of 16x16 pixels and titles for each sub menu. But
only if a menu with the name *preferences* exists in the users or system
wide Xdg directories. Else it\'s empty!

To add the generated menu to the "Utilities" menu for example put the
following to your fvwm config file (~/.fvwm/config or ~/.fvwm/.fvwm2rc):

  ::

      AddToMenu Utilities "Preferences Menu" Popup FvwmPref
      PipeRead 'fvwm-menu-desktop --desktop kde --menu-type preferences \
                                  --title FvwmPref [other options]'

If you think that **fvwm-menu-desktop** slows down your menu startup too
much do not use **PipeRead**. Instead run **fvwm-menu-desktop** and
redirect the menu to a file and read that file in your .fvwm2rc file.

  ::

      AddToMenu MenuRoot "XDG Menus" Popup FvwmMenu
       ...

      AddToMenu FvwmMenu
      + DynamicPopupAction Function FuncRecreateXdgMenus
       ...


      DestroyFunc FuncRecreateXdgMenus
      AddToFunc   FuncRecreateXdgMenus
      + I Test (f  $[FVWM_USERDIR]/.menu) Read $[FVWM_USERDIR]/.menu
      + I TestRC (!Match) PipeRead 'fvwm-menu-desktop > $[FVWM_USERDIR]/.menu \
                                    &&  echo "Read $[FVWM_USERDIR]/.menu"'

or if you want to show the menus directly in a normal "Root" menu use
this:

  ::

      AddToMenu MenuRoot "Root Menu" Title
      + FuncXdgMenusInRoot
       ...


      DestroyFunc FuncXdgMenusInRoot
      AddToFunc   FuncXdgMenusInRoot
      + I Test (f  $[FVWM_USERDIR]/.menu) Read $[FVWM_USERDIR]/.menu
      + I TestRC (!Match) PipeRead 'fvwm-menu-desktop --insert-in-menu MenuRoot \
                                    > $[FVWM_USERDIR]/.menu \
                                    && echo "Read $[FVWM_USERDIR]/.menu"'

The problem here is, that you have to restart fvwm because items
insserted into such a menu cannot be removed. For that BOTH menus must
be regenerated:

  ::

      AddToMenu MenuRoot DynamicPopupAction FuncMenuRoot

      DestroyFunc FuncMenuRoot
      AddToFunc FuncMenuRoot
      + I DestroyMenu MenuRoot
      + I AddToMenu MenuRoot DynamicPopupAction FuncMenuRoot
      + I AddToMenu MenuRoot "Root Menu" Title
      + I Popup XdgMenus

      AddToMenu XdgMenus DynamicPopupAction FuncXdgMenusInRoot


      DestroyFunc FuncXdgMenusInRoot
      AddToFunc FuncXdgMenusInRoot
      + I AddToMenu XdgMenus DynamicPopupAction FuncXdgMenusInRoot
      + I Test (f  $[FVWM_USERDIR]/.menu) Read $[FVWM_USERDIR]/.menu
      + I TestRC (!Match) PipeRead 'fvwm-menu-desktop --insert-in-menu MenuRoot \
                                    > $[FVWM_USERDIR]/.menu \
                                    && echo "Read $[FVWM_USERDIR]/.menu"'

GUI
---

There\'s a **FvwmForm** GUI to setup the menu generation manually. It is
found in the root of the generated menu called "Regenerate XDG Menu(s)".

Or it can be started from within **FvwmConsole** with

  ::

      Module FvwmPerl -l fvwm-menu-desktop-config.fpl

BUGS
----

The whole process of creating menus from files is slow. Otherwise report
bugs to the fvwm-workers mailing list <fvwm-workers@fvwm.org>.

AUTHORS
-------

This script is based on fvwm-xdg-menu.py written by Piotr Zielinski
(http://www.cl.cam.ac.uk/~pz215/) who assigned Licence: GPL 2 Date:
03.12.2005.

The script was reworked to replace the existing fvwm-menu-desktop perl
script by the fvwm-workers.

COPYING
-------

The script is distributed by the same terms as fvwm itself. See GNU
General Public License for details.
