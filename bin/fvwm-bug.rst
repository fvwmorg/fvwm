========================================================================
fvwm-bug
========================================================================

------------------------------------------------------------------------
report a bug in fvwm
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

**fvwm-bug** [*--help*] [*--version*] [*address*]

DESCRIPTION
-----------

**fvwm-bug** is a shell script to help the user compose and mail bug
reports concerning fvwm in a standard format. **fvwm-bug** invokes the
editor specified by the environment variable **EDITOR** on a temporary
copy of the bug report format outline. The user must fill in the
appropriate fields and exit the editor. **fvwm-bug** then mails the
completed report to the local fvwm maintainer, the fvwm workers list
*fvwm-workers@fvwm.org*, or *address*. If the report cannot be mailed,
it is saved in the file *dead.fvwm-bug* in the invoking user\'s home
directory.

The bug report format outline consists of several sections. The first
section provides information about the machine, operating system, the
fvwm version, and the compilation environment. The second section should
be filled in with a description of the bug. The third section should be
a description of how to reproduce the bug. The optional fourth section
is for a proposed fix. Fixes are encouraged.

ENVIRONMENT
-----------

**fvwm-bug** will utilize the following environment variables if they
exist:

**EDITOR**  Specifies the preferred editor. If **EDITOR** is not set, **fvwm-bug** defaults to **emacs**.

**HOME**    Directory in which the failed bug report is saved if the mail fails.
