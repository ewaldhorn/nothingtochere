# Sudoku Solver

Simple Sudoku solver in good old C.

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
Input:
`53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79`

Expected:
`534678912672195348198342567859761423426853791713924856961537284287419635345286179`
