const std = @import("std");

const cString = @cImport({
    @cInclude("string.h");
});

// --------------------------------------------------------------------- strlen
// Zig wrapper about C strlen
fn strlen(str: [:0]const u8) usize {
    return cString.strlen(str);
}

// --------------------------------------------------------------------- strdup
// Zig wrapper around C strdup
fn strdup(str: [:0]const u8) ![*:0]u8 {
    return cString.strdup(str) orelse error.OutOfMemory;
}

// --------------------------------------------------------------- strdup_safer
// Zig wrapper around C strdup that's a bit safer to use
fn strdup_safer(allocator: std.mem.Allocator, str: [:0]const u8) ![:0]u8 {
    const cCopy: [*:0]u8 = cString.strdup(str) orelse return error.OutOfMemory;
    defer std.c.free(cCopy);

    // Create a Zig slice of the C buffer that's length-aware.
    const zCopy: [:0]u8 = std.mem.span(cCopy);

    // Allocate a new null-terminated Zig-managed slice and copy in the contents
    // of zCopy.
    return allocator.dupeZ(u8, zCopy);
}

// ======================================================================= main
pub fn main() !void {
    const s = "hello";
    std.debug.print("s is type {s} with a length of {d} characters.\n", .{ @typeName(@TypeOf(s)), s.len });
    std.debug.print("The actual size of s is {d} bytes, including the NULL terminator.\n", .{@sizeOf(@TypeOf(s.*))});

    std.debug.print("C thinks that s contains {d} characters.\n", .{strlen(s)});

    const sCopy = try strdup(s);
    defer std.c.free(sCopy); // gotta remember to free memory allocated in C
    std.debug.print("sCopy= [{s}] (type={}, size={d}, len={d})\n", .{ sCopy, @TypeOf(sCopy), @sizeOf(@TypeOf(sCopy)), std.mem.len(sCopy) });

    // going to need to grab some ram
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer _ = gpa.deinit();

    const saferCopy = try strdup_safer(allocator, s);
    defer allocator.free(saferCopy);
    std.debug.print("saferCopy= [{s}] (type={}, size={d}, len={d})\n", .{ sCopy, @TypeOf(saferCopy), @sizeOf(@TypeOf(saferCopy)), saferCopy.len });
}
