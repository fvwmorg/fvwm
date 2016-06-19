========================================================================
fvwm-convert-2.4
========================================================================

------------------------------------------------------------------------
convert fvwm 2.2.x configuration file to fvwm 2.4
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1

syntax

SYNOPSIS
--------

**fvwm-convert-2.4** [*source*] [*dest*]

DESCRIPTION
-----------

**fvwm-convert-2.4** converts an fvwm 2.2.x configuration file into an
fvwm 2.4 compatible syntax. It is not suitable to convert older 1.x
configuration files. Please use **fvwm-convert-2.2** to convert these to
the 2.2.x format first.

By default, **fvwm-convert-2.4** converts *~/.fvwm2rc,* saving the
results in *~/.fvwm/.fvwm2rc.* You must create the *~/.fvwm* directory
before running this command. Starting with the 2.4 release, the
directory *~/.fvwm* is the default location for fvwm user configuration
files. Different source and destination files may be given. If the
destination file already exists, this program exits. While the program
runs it will generate a temporary file with the same name as the
destination file with the suffix ".pass1" added.

**fvwm-convert-2.4** makes the following changes:

**PixmapPath/IconPath**
  In fvwm 2.4, the PixmapPath and IconPath commands are replaced by the
  ImagePath command. In addition, the ImagePath can be compiled into fvwm.
  **fvwm-convert-2.4** changes the PixmapPath and IconPath commands to
  ImagePath commands and removes any directories that are compiled into
  fvwm. Paths starting with a dollar sign are also removed.

**ModulePath**
  In fvwm 2.4, the ModulePath is compiled into fvwm. **fvwm-convert-2.4**
  removes any ModulePath commands it finds. If you are using your own
  modules, (not the ones that come with fvwm), you will have to fix your
  configuration file after using **fvwm-convert-2.4**.

**HilightColor**
  In fvwm 2.4, the HighlightColor command is replaced by a Style command
  using the HilightFore and HilightBack arguments. **fvwm-convert-2.4**
  makes these changes.

**HilightColorset**
  In fvwm 2.4, the HighlightColorset command that was present in some of
  the 2.3.x beta releases is replaced by a Style command using the
  HilightColorset style. **fvwm-convert-2.4** makes these changes.

**WindowShadeAnimate**
  In fvwm 2.4, the WindowShadeAnimate command is replaced by the
  WindowShadeSteps Style option. **fvwm-convert-2.4** makes this change.

**WindowFont**
  In fvwm 2.4, the WindowFont command is replaced by a Style command using
  the Font argument. **fvwm-convert-2.4** makes this change.

**ColorLimit**
  In fvwm 2.4, the ColorLimit command is automatic. If you have a limited
  colormap, color limiting is the default. **fvwm-convert-2.4** removes
  any ColorLimit command that it finds.

**GlobalOpts**
  The GlobalOpts command is converted to **Style** options and the
  **BugOpts** command. Some options can not be converted automatically,
  though.

**Read**
  Prints a message identifying any read commands found. The files being
  read may need to be converted also.

**Placement Styles**
  Any of the old placement Styles found in the file can not be converted
  automatically. Instead, **fvwm-convert-2.4** prints a warning. For
  details about the conversion, please refer to the "Window manager
  placement" section of the fvwm man page.

**FvwmConfig and FvwmPipe**
  These modules are no longer a part of the fvwm distribution.
  **fvwm-convert-2.4** prints a warning if these modules are found in the
  file.

**FvwmButtons panels**
  The syntax of panels in FvwmButtons has changed. The conversion can not
  be done automatically. **fvwm-convert-2.4** prints a message when it
  encounters a potential panel definition. For details about the
  conversion, please refer to the "CONVERTING OLD PANEL CONFIGURATIONS"
  section of the FvwmButtons man page.

BUGS
----

You need Perl to be installed.

*WindowFont* and *HilightColor* commands embedded in functions are not
found. If you have either of these commands in functions, they are not
detected.

Known bugs can be found in the fvwm bug tracking system (accessible from
the fvwm home page).

Bug reports can be sent to the fvwm-workers mailing list (see the
*FAQ*).

AUTHOR
------

Dan Espen <despen@telcordia.com>.
