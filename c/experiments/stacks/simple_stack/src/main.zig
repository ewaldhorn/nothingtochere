const std = @import("std");

const stack = @cImport({
    @cInclude("simple_stack.c");
});

pub fn main() void {
    _ = stack.push(5);
    _ = stack.push(4);
    _ = stack.push(3);
    _ = stack.push(2);
    _ = stack.push(1);

    std.debug.print("Stack: {any}   Top: {d}  Head: {d}  Popped: {d}  Popped: {d}\n", .{ stack.theStack, stack.top, stack.peek(), stack.pop(), stack.pop() });
}

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

// ----------------------------------------------------------------------------
test "push multiple values and pop in sequence" {
    stack.clear();

    _ = stack.push(5);
    _ = stack.push(4);
    _ = stack.push(3);
    _ = stack.push(2);
    _ = stack.push(1);

    try expect(stack.push(0) == false); // stack is already full

    try expect(stack.top == 4); // 0..4 is 5 elements
    try expect(stack.peek() == 1);

    try expect(stack.pop() == 1);
    try expect(stack.pop() == 2);
    try expect(stack.pop() == 3);
    try expect(stack.pop() == 4);
    try expect(stack.pop() == 5);

    try expect(stack.pop() == stack.STACK_EMPTY);
}
