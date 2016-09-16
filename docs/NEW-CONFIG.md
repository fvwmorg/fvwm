New Configuration Format
========================

Introduction
============

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

Syntax
======

**[These are rough ideas for now...]**:

* Still line-based.
* Structured information can be represented like this:

  ```
  Function -n func_name -i DoImmediate -c DoClick -h DoHold
  ```

  **But this doesn't take into account the ordering of the commands to run.**

  Maybe:

  ```
  Function -n func_name "i:DoImmediate,c:DoClick,i:DoImmediate,h:DoHold"
  ```

* Ways of referring to windows/desks/monitors, etc:

  ```
  -t: screen:desk.page
  -w: n:name, c:class, r:resource|<win_id>|*
  -g  (global)
  ```

  Example:

  ```
  Style -w n:xteddy, c:XTeddy InitialMapCommand Sticky
  Next -tfoo:1 -w c:XTeddy Echo "Found XTeddy on screen 'foo', desk 1"
  ```

  Hence, `-t` and `-w` are consistent throughout the entirety of the command
  set in FVWM.

* Setting options:

  ```
  -g (global)
  -t screen:desk.page
  ```

* Bindings:

  ```
  -k: key
  -m: mouse
  cmd
  ```

  Example:

  ```
  bind -k CSM-w Close
  bind -m 1 Close -t ...
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
Focus -t+1

# Focus next window on monitor 1.
Focus -t1:+1

# Focus third window on monitor 1
Focus -t1:+3
```
