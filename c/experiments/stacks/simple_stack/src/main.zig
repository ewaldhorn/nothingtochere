const std = @import("std");

const stack = @cImport({
    @cInclude("simple_stack.c");
});

pub fn main() void {}

// ====================================================================== TESTS
const expect = std.testing.expect;

// ----------------------------------------------------------------------------
test "pop empty stack" {
    const result = stack.pop();
    const expectedResult = stack.STACK_EMPTY;

    try expect(result == expectedResult);
}

// ----------------------------------------------------------------------------
test "push onto stack succeed" {
    const result = stack.push(1);
    try expect(result);
}

// ----------------------------------------------------------------------------
test "push and pop succeed" {
    const pushResult = stack.push(12);
    const popResult = stack.pop();

    try expect(pushResult);
    try expect(popResult == 12);
}
