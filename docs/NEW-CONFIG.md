New Configuration Format
========================

Introduction
============

FVWM is completely governed by how it reads in commands, and hence at the
moment, each command is responsible for parsing its values.  There's been
twenty years of this idea; organically growing out of control.  Adding or even
changing existing options to commands is a nightmare; there's no state being
kept between commands (which would be good), and hence there's a lot of the
same sorts of information being gathered separately, leading to a lot of
duplication at the code-level.

Changing the format is a great way of getting a clean break, and being able to
rationalise the commands we have now, and need; moving functionality into
other commands in an extensible way, which will also reduce the code
complexity somewhat.  You can't easily do this with the format we have now.

FVWM's configuration format is line-based.  This means, each line is parsed by
itself, without any structure.  This means, groups of commands such as
*functions* have no structural representation, other than to end with a blank
line.  For example:

```
DestroyFunc Foo
AddToFunc   Foo
+ I DoAThing
+ I DoAnotherThing

```

Indeed, because of this, structure has been represented through complexity;
the **+** command was created to address the fact that there was no grouping,
and hence the **+** command operates over *functions*, and *decor* commands.

Added to this is the fact that each possible command in FVWM (including how
that's represented in the configuration file) does its own parsing, leading to
a complete myriad of differences and duplication.

A new configuration file therefore must accept structural data, and have it
represented appropriately.  Commands should receive information rather than
having to parse it itself.

If the syntax were like mini-CLI programs, this would make scripting a lot
easier; reducing the need for FvwmCommand/FvwmConsole (or rather making it
easier to implement replacements for them.)

Migration
=========

There will be a means of going from the current FVWM format to whatever new
one is put in place, via conversion script(s).  It is doubtful theser scripts
will be able to convert everything, but they will do their best.  This is no
different to the current set of conversion scripts that have been written for
previous versions of FVWM.

Syntax
======

**[These are rough ideas for now...]**:

* Still line-based.

* Line-continuation character '\' still supported.

* Here-docs can be used as well to reduce the "visual clutter":

  ```
  Function -nfoo <<EOF
	i:DoThis
	c:DoThat
	m:MoveMe
  EOF
  ```

* Functions:

  ```
  -n: function name

  i:Immediate Action
  c:Click Action
  m:Motion Action
  h:Hold Action
  d:Double-click Action
  ```

  Example:


  ```
  Function -n func_name " \
	  i:DoImmediate, \
	  c:DoClick, \
	  i:DoImmediate, \
	  i:TestRc (NoMatch) Break, \
	  h:DoHold"
  ```

* Ways of referring to windows/desks/monitors, etc:

  ```
  -t: screen:desk.page
  -w: n:name, c:class, r:resource|<win_id>|*|-<NUM>|+<NUM>
  -g  (global)
  ```

  Example:

  ```
  Style -w n:xteddy, c:XTeddy InitialMapCommand Sticky
  Next -tfoo:1 -w c:XTeddy Echo "Found XTeddy on screen 'foo', desk 1"
  ```

  Hence, `-t` and `-w` are consistent throughout the entirety of the command
  set in FVWM.

  Relative positional arguments can be specified:

  ```
  -t :+1 -- goto next desk
  -t :-1 -- goto previous desk
  -t +1  -- goto next monitor

  -w -1  -- the previous window (stack ring)
  -w +3  -- the third window (stack ring)
  -w c:XTerm,+3 -- the third XTerm window
  ```

  **TODO:** What happens if there's more than one match?  Menu popup?

* Setting options:

  ```
  -g (global)
  -t screen:desk.page
  ```

* Environment variabes:

  ```
  foo = bar
  ```

  Interpolation:

  ```
  $foo
  ```

* Bindings:

  ```
  -k: key
  -m: mouse
  -c: context (A|W|M|F|S|etc...)
  cmd
  ```

  Example:

  ```
  bind -k CSM-w -cAll Close
  bind -m 1 -cW Close -t ...
  ```

* Menus:
 
  ```
  -n: name of menu
  -i: item name of command to run
  command
  ```

  Example:


  ```
  menu -n menu_name -i item_name command1
  menu -n menu_name -i item_name command2
  menu -n menu_name -i item_name command3
  ```

* Hooks:

  Moves FvwmEvent to the core; hooks are first-class citizens.
  Do we want to consider the notion of before/after hooks?

  ```
  -g  (global)
  -n: hook event name.
  -t: as other commands
  ```

  ```
  hook -g -nbefore-map Echo "About to map a window..."
  hook -nafter-map Echo "I just mapped $[w.name]"
  ```

* Colorsets:

  ```
  -n: name of colorset
  -f: foreground colour
  -b: background colour
  -h: highlight colour
  -s: shade colour
  -t: transparent
  ```

  Example:

  ```
  Colorset -nwindows -fwhite -bgreen -t
  ```

* Modules:

  Unclear -- likely not going to change, since that's orthogonal to how they
  could work; the "*" syntax for modules can still be line-based as it is now.

Rough Example
=============

```
Colorset -n1 -b red  -f red
Colorset -n2 -b blue -f blue

# Log new window names...
hook -g -nafter-map Echo "Mapped $[w.name]"

# Make all clients on screen 0, desk 1, red...
Style -t 0:1 -w* Colorset 1

# Make only XTerm windows on any screen blue
Style -g -w c:XTerm Colorset 2

# Focus next window on current monitor.
Focus -w+1

# Focus next window on monitor 1.
Focus -t1 -w+1

# Focus third window on monitor 1
Focus -t1 -w+3

# Focus previous window
Focus -w-1

# Focus the next XTerm window on the previous desk
Focus -t:-1 -wc:XTerm
```

Reference Implementation
========================

There's the beginnings of a CLI application to show how the parsing would
work, without needing to change FVWM just yet.

This is just a means of fleshing out the data structures and behaviour would
be, and to start to amalgamate functionality between duplicate commands.

* [Refence Program](../config/config.c)
* [Sample Config](../config/config_file)
