========================================================================
FvwmConsoleC.pl
========================================================================

------------------------------------------------------------------------
Command editor for fvwm command input interface
------------------------------------------------------------------------

:Date: |date|
:Manual section: 1


SYNOPSIS
--------

FvwmConsole -e /usr/X11/lib/fvwm/FvwmConsoleC.pl

COPYRIGHT
---------

Copyright 1996, Toshi Isogai. No guarantees or warranties are provided.
Use this program at your own risk. Permission to use this program for
any purpose is given, as long as the copyright is kept intact.

DESCRIPTION
-----------

FvwmConsoleC.pl offers editing capabilities while the user is entering
the line. By default, the line editing commands are similar to those of
emacs. It also offers **substitution** , which replaces a pattern to a
string before it sends the command.

FUNCTIONS
---------

Functions are bound to a key or key combination to be invoked. The
followings are functions available and their default key bindings.

**bind** *Meta-k, Ctrl-x Ctrl-b*
  
  List up key bindings and substitutions.

**boh**
  
  Move to the beginning of history.

**boh\_ign\_mode** *Esc-<*
  
  Move to the beginning of history. If it is in search mode, continue.

**bol** *Home, Ctrl-a*
  
  Move cursor to the beginning of the line.

**bs[(n)]** *BackSpace, Ctrl-h*
  
  Backspace n times. default of n is 1.

**cancel** *Ctrl-x, Ctrl-k*
  
  Cancel the current input.

**del\_back\_line**
  
  Delete the line from the beginning to the cursor.

**del\_back\_word** *Ctrl-w*
  
  Delete the word from the beginning to the cursor.

**del\_char [(n)]** *Delete, Ctrl-d*
  
  Delete n characters from the cursor to the right. Default of n is 1.

**del\_forw\_line** *Ctrl-k*
  
  Delete the line from the cursor to the end.

**del\_forw\_word** *Meta-d*
  
  Delete the word from the cursor to the end.

**del\_line** *Ctrl-u*
  
  Delete the entire line.

**enter** *Enter, Ctrl-j, Ctrl-m*
  
  Perform substitution if applicable and send the line to fvwm.

**enter\_wo\_subst** *Meta-Enter*
  
  Send the line to fvwm without any substitution.

**eoh**
  
  Move to the end of history.

**eoh\_ign\_mode** *Esc->*
  
  Move to the end of history. If it is in search mode, continue.

**eol** *End, Ctrl-e*
  
  Move the cursor to the end of line.

**ins\_char (str)**
  
  Insert string at the cursor.

**ins\_last\_word** *Esc-.*
  
  Insert the last argument of the previous command at the cursor.

**ins\_nth\_word** *Meta-[1..9]*
  
  Insert the n-th argument of the previous command at the cursor.

**list\_func** *Meta-l*
  
  List up available editing functions.

**next\_char** *Right, Ctrl-f*
  
  Move the cursor to the next character.

**next\_line** *Down, Ctrl-n*
  
  Move to the next line in history.

**next\_word** *Meta-f*
  
  Move the cursor to the next word.

**prefix**

  Wait for the next character typed in for multi-key binding.

**prev\_char** *Left, Ctrl-b*
  
  Move the cursor to the previous character.

**prev\_line** *Up, Ctrl-p*
  
  Move to the previous line in history.

**prev\_word** *Meta-b*
  
  Move the cursor to the previous word.

**quote** *Ctrl-q*
  
  Insert the next character typed into the buffer literally.

**search** *Ctrl-s*
  
  Search pattern in history.

**search\_rev** *Ctrl-r*
  
  Search pattern in history in reverse order.

**subst** *Meta-s*

  Substitute all patterns to strings and reprint the line. The
  substitutions are not nested and performed in the order that they are
  defined.

CONFIGURATION
-------------

The key binding can be overridden or defined in fvwm module
configuration.

::

  *FvwmConsole: Key \ck prev_line

Non-space character sequence need not be quoted. In order to undefine,
omit the last argument.

::

  *FvwmConsole: Key \ck

Note that non-meta character is case sensitive. \\c means control key,
\\e means escape, and \\m is alt key.
It also accepts Subst configuration. Users often input long fvwm
command repeatedly. Subst will replace particular input sequence to
user defined string. Example:

::

  *FvwmConsole: Subst '^bigx' 'Exec xterm -g 120x60+0+0 -fn 10x20 -fg 
  black -bg lemonchiffon'

Typing \'bigx<return>\' in FvwmConsole will launch xterm. \'^\' denotes the
beginning of line in **regular expression.** ´pl´ in the middle of the
command will not be replaced. Although the format looks different, it
takes Perl regular expression. It just uses single or double quote as
the delimiter. Single or double quotes have no difference, although they
have to match, and cannot include itself in the string.

::

  *FvwmConsole: Subst '^g\s*(\d+)' 'Desk 0 0\nGotoPage 0 $1\nFocus'

Entering \'g4\' or \'g 4\' will jump to desk 0 page 0 4 and focus.

INVOCATION
----------

FvwmConsoleC.pl should be invoked by FvwmConsole.

SEE ALSO
--------

FvwmConsole(1x), perlre(1)

AUTHOR
------

Toshi Isogai
