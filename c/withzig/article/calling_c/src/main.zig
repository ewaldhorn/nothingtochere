const std = @import("std");

const cStringFunctions = @cImport({
    @cInclude("string.h");
});

const cMyMath = @cImport(@cInclude("my_math.c"));

pub fn main() void {
    const myString = "This is my string, it contains 45 characters.";
    std.debug.print("Zig: '{s}' contains {d} characters.\n", .{ myString, myString.len });
    std.debug.print("C: '{s}' contains {d} characters.\n", .{ myString, cStringFunctions.strlen(myString) });

    const left = 26;
    const right = 16;
    std.debug.print("The sum of {d} and {d} is {d}.\n", .{ left, right, cMyMath.summer(left, right) });
}

test "Zig and C agree on string lengths" {
    const inputString = "This is the input string we will use for this test.";
    const zigLength = inputString.len;
    const cLength = cStringFunctions.strlen(inputString);

    try std.testing.expect(zigLength == cLength);
}

test "Zig calling a custom C function" {
    const left = 28;
    const right = 14;
    const expected = 42;
    const result = cMyMath.summer(left, right);

    try std.testing.expect(result == expected);
}
