<h1 align="center">
MINISHELL
</h1>

<h4 align="center">
As beautiful as a shell !!
</h4>
</p>

<h3 align="center">
	<a href="#about">[About]</a>
	<span> · </span>
	<a href="#index">[Index]</a>
	<span> · </span>
	<a href="#usage">[Usage]</a>
	<span> · </span>
	<a href="#useful-links">[Useful Links]</a>
</h3>

## About
___
Minishell, as part of the 42 curriculum, is a simplified version of a UNIX shell. This project is designed to introduce students to the basics of system programming, process management, and interaction with the kernel via a user-created command interpreter.

____
## Index
___
### Project Objectives

The goals of Minishell are:
- Emulate the basic functionality of a traditional UNIX shell.
- Interpret commands entered by the user.
- Implement error and signal handling.
- Manage environment and local variables.
- Handle input/output redirections and pipes.

### Implemented Features

In this version of Minishell, the following features have been implemented:
- Basic command interpretation and execution.
- Error and signal management.
- Environment and local variables management.
- Simple (<, >) and advanced (<<, >>) redirections.
- Pipe mechanisms (|).
- Built-in commands like `echo`, `cd`, `env`, `export`, `unset`, and `exit`.

### Non-Implemented Features

Some advanced features not covered include:
- Complex chaining of commands with semicolons (;).

### Conclusion

The Minishell project provides a hands-on approach to understanding the inner workings of a shell, teaching valuable skills in systems programming and process management. It's a critical step for students at École 42 to deepen their understanding of operating system fundamentals.

## Usage
___
### Instructions

**1. Compiling & Executing the program**

To compile and execute the program, run:

```shell
$ make
$ ./minishell
```
**3. Special Compiling Rules**

To compile the program with valgrind, run:

```shell
$ make leak
```

## Useful Links
* [42 Docs - minishell](https://harm-smits.github.io/42docs/projects/minishell)
* [Bash Guide for Beginners](https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html)
* [Useful notes on Shell & Shell Scripting](https://www.notion.so/Shell-Shell-Scripting-6e0f0290a0304dad93a1d25ba15d92fe)
* [The Open Group Base Specifications - Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [Introduction to Systems Programming: a Hands-on Approach - Chapter 5. Writing Your Own Shell ](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

by [mpitot](https://github.com/MPIT0T) & [mbrousse](https://github.com/maxdegers).
