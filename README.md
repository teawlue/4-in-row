# Connect Four in C++

This project is an implementation of the classic game "Connect Four" where two players drop tokens into a grid, attempting to be the first to align four tokens in a row, either vertically, horizontally, or diagonally.

## Compilation and Execution

This program is written in C++ and can be compiled with any standard C++ compiler such as `g++`.

### Prerequisites

- A C++ compiler (e.g., G++ or Clang)
- Command line terminal

### Compiling the Code

To compile the code, you can use the following command in your terminal:

```
g++ -o 4_in_row 4 in row.cpp
```

Replace `4_in_row.cpp` with the path to the source code file if it is located in a different directory.

### Running the Program

After compiling the code, you can run the program using:

```
./4 in row
```

## Game Description

The game board is a grid of 8 rows by 8 columns. Players take turns dropping their tokens ('X' for Player and 'O' for AI) into the columns. The tokens fall to the lowest available space within the column. The game ends when a player aligns four of their tokens consecutively or the board fills up, resulting in a draw.

## Implementation Details

The implementation consists of several functions that manage the game logic:

### `initializeBoard()`

This function sets up the game board by initializing an 8x8 grid filled with zeros (representing empty cells).

### `printBoard()`

Prints the current state of the board to the console, marking the last move differently to highlight recent moves.

### `makeMove(int col, int player)`

Attempts to place a token for the specified player in the specified column:
- `col`: The column where the token is to be placed.
- `player`: The player making the move, either `PLAYER` (1) or `AI` (2).

This function returns `true` if the move was successful, `false` otherwise.

### `checkWin(int player)`

Checks whether the specified player has won the game by aligning four tokens in a row. This function checks horizontally, vertically, and diagonally.

### `isFull()`

Checks if the board is completely filled with tokens, which would result in a draw if no player has won.

### `minimax(int depth, bool maximizingPlayer, int alpha, int beta)`

Implements the minimax algorithm with alpha-beta pruning to determine the best move for the AI:
- `depth`: The current depth of recursion.
- `maximizingPlayer`: `true` if the function is currently evaluating the maximizing player's move, `false` otherwise.
- `alpha`: The current best value achievable by the maximizer.
- `beta`: The current best value achievable by the minimizer.

This function returns the heuristic value of the board from the perspective of the AI.

## Alpha-Beta Pruning

Alpha-beta pruning is an optimization technique for the minimax algorithm that reduces the number of nodes evaluated in the search tree. It works by passing two extra parameters:
- `alpha`: The best already explored option along the path to the root for the maximizer.
- `beta`: The best already explored option along the path to the root for the minimizer.

If the minimax value of a position is better than the current `alpha` for the maximizer, `alpha` is updated. If it is worse than the current `beta` for the minimizer, the branch is pruned and not explored further.

This technique significantly improves the performance of the minimax algorithm, allowing it to search deeper in the game tree within the same amount of time.
