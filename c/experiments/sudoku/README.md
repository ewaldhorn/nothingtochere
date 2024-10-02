# Sudoku Solver

Simple Sudoku solver in good old C.  I used Zig as the compiler/runner.

Sudoku consists of 81 blocks (9x9) in total.
Numbers are 1..9.
There are 9 3x3 blocks.
Each block contains 1..9, so that each full row/column does not repeat any digit.

See <https://en.wikipedia.org/wiki/Sudoku> for the real facts :P

## Sample input

Puzzle:
2  6 3 1
31 9 2
8     52
78 961
4 1 7 2
 528 67
89     1
  3 9 68
4 3 2  9

Leads to input:

`.2..6.3.131.9.2....8.....52.78.961...4.1.7.2...528.67.89.....1....3.9.684.3.2..9.`

## Testing

There are some primitive tests in the `test.c` file. The `test.sh` can be used to run them.
Tests can either be hard-coded or added to the `tests.txt` file. An input line followed by an expected line will create one test.

For example:

`53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79`

`534678912672195348198342567859761423426853791713924856961537284287419635345286179`

Sample 1
Input:
`53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79`

Expected:
`534678912672195348198342567859761423426853791713924856961537284287419635345286179`

Sample 2
Input:
`4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......`

Expected:
`417369825632158947958724316825437169791586432346912758289643571573291684164875293`

## Linting

I used `semgrep scan --config auto`
