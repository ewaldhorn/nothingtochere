# Build C sources with Zig

How to use Zig to build pure C code.

## Build helloworld.c

The following command will produce an executable binary called `howdy`:

`zig cc helloworld.c -o howdy`

You can use `file howdy` to verify that it is indeed a binary for your platform.

## Target other platforms:

Use `zig cc helloworld.c -o howdyLinux -target aarch64-linux-gnu` to target Linux.
