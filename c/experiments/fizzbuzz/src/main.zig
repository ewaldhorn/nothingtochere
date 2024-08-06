const std = @import("std");

const fizzBuzzer = @cImport({
    @cInclude("fizz_buzzer.c");
});

const cStrings = @cImport({
    @cInclude("string.h");
});

// ----------------------------------------------------------------- getVersion
fn getVersion() [*:0]u8 {
    const result = fizzBuzzer.version();
    std.debug.print("\n!!!\nResult {any}\n!!!\n", .{result});
    return result;
}

// --------------------------------------------------------------------- strdup
fn strdup(str: [:0]const u8) ![*:0]u8 {
    return cStrings.strdup(str) orelse error.OutOfMemory;
}

// ======================================================================= MAIN
pub fn main() void {}

// ====================================================================== TESTS
const expect = std.testing.expect;

// ----------------------------------------------------------------------------
test "call C to duplicate a string" {
    const s = "hi";
    std.debug.print("\ns    = [{s}] (type={}, size={d}, len={d} address={*})\n", .{ s, @TypeOf(s), @sizeOf(@TypeOf(s.*)), s.len, s });
    const sCopy = try strdup(s);
    defer std.c.free(sCopy);
    std.debug.print("sCopy= [{s}] (type={}, size={d}, len={d} address={*})\n", .{ sCopy, @TypeOf(sCopy), @sizeOf(@TypeOf(sCopy)), std.mem.len(sCopy), sCopy });
}

// ----------------------------------------------------------------------------
// test "zig calling C to get length of string" {
//     const input = "One two three!";
//     const result = cStrings.strlen(input);

//     try expect(result == input.len);
// }

// ----------------------------------------------------------------------------
// test "zig receiving a string from C" {
//     const result: [*:0]u8 = getVersion();
//     const expected = "0.0.1";

//     std.debug.print("Result: {any}", .{result});
//     std.debug.print("Expected: {any}", .{expected});

//     // try expect(std.mem.eql(u8, result, expected));
// }

// ----------------------------------------------------------------------------
test "1 => 1" {
    const result = true;
    const expectedResult = true;

    try expect(result == expectedResult);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
