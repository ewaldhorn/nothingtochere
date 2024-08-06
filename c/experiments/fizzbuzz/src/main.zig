const std = @import("std");

const fizzBuzzer = @cImport({
    @cInclude("fizz_buzzer.c");
});

const cStrings = @cImport({
    @cInclude("string.h");
});

pub fn main() void {}

// ====================================================================== TESTS
const expect = std.testing.expect;

// ----------------------------------------------------------------------------
test "zig calling C to get length of string" {
    const input = "One two three!";
    const result = cStrings.strlen(input);

    try expect(result == input.len);
}

// ----------------------------------------------------------------------------
test "1 => 1" {
    const result = true;
    const expectedResult = true;

    try expect(result == expectedResult);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
