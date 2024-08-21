# Basic C Template

This is a simple C template I use for new projects. It assumes [Zig](https://ziglang.org/) and [Task](https://taskfile.dev/) are installed.

Zig is used as the compiler / runner of the C code while Task is used instead of Make. Why? Because I like Task, that's why!

## Zig

I'm using Zig 0.13.0 as the C compiler in this project on a Mac, but it should work on just about any platform.

## Task

Task is a brilliant tool written in Go that allows you to execute tasks defined in a simple YAML file. I put all the commands I use in there, since it just makes life easier.

### Running

Use `task` by itself in the terminal to get a list of available tasks.
