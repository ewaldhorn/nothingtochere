# Basic C Template

This is a simple C template I use for new projects. It assumes [Zig](https://ziglang.org/) and [Task](https://taskfile.dev/) are installed.

Zig is used as the compiler / runner of the C code while Task is used instead of Make. Why? Because I like Task, that's why!

## Zig

I'm using Zig 0.13.0 as the C compiler in this project on a Mac, but it should work on just about any platform.

## Task

Task is a brilliant tool written in Go that allows you to execute tasks defined in a simple YAML file. I put all the commands I use in there, since it just makes life easier.

### Available tasks

Use `task` by itself in the terminal to get a list of available tasks. Some of the tasks are:

- `task` To see the list of tasks
- `task clean` to remove build artifacts
- `task build` To build the binaries to the 'bin' folder
- `task run` To run the 'main.c' file using Zig
- `task test` To run the C-based tests
- `task license` To display the license
- `task readme` To display the readme

### Going further

If you are interested, you also look at [using the Zig build system](https://github.com/allyourcodebase) as a really nice replacement for traditional `make` files. Zig is a great toolchain and programming language, but you don't need to use Zig for your C projects if you don't want to. Instead, you can leverage the power of the toolchain with this project and keep using C as your favourite language.

### What about make

Of course, `make` is not going anywhere, so I've included an example `Makefile` as well, for those that prefer to keep using it, it is a well-known and powerful tool after all.
