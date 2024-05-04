#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

const int ROWS = 8;
const int COLS = 8;
const int EMPTY = 0;
const int PLAYER = 1;
const int AI = 2;
int aiDepth = 7; // Глубина для ИИ

std::vector<std::vector<int>> board(ROWS, std::vector<int>(COLS, EMPTY));
std::pair<int, int> lastMove{ -1, -1 };

void initializeBoard() {
    for (auto& row : board) {
        std::fill(row.begin(), row.end(), EMPTY);
    }
}

void printBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == lastMove.first && j == lastMove.second) {
                std::cout << (board[i][j] == PLAYER ? 'x' : 'o') << " ";
            }
            else {
                if (board[i][j] == PLAYER) {
                    std::cout << 'X' << " ";
                }
                else if (board[i][j] == AI) {
                    std::cout << 'O' << " ";
                }
                else {
                    std::cout << '.' << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "0 1 2 3 4 5 6 7" << std::endl;
}

bool makeMove(int col, int player) {
    if (col >= 0 && col < COLS && board[0][col] == EMPTY) {
        for (int row = ROWS - 1; row >= 0; --row) {
            if (board[row][col] == EMPTY) {
                board[row][col] = player;
                lastMove = { row, col };
                return true;
            }
        }
    }
    return false;
}

bool checkWin(int player) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if ((c <= COLS - 4) &&
                (board[r][c] == player && board[r][c + 1] == player &&
                    board[r][c + 2] == player && board[r][c + 3] == player))
                return true;
            if ((r <= ROWS - 4) &&
                (board[r][c] == player && board[r + 1][c] == player &&
                    board[r + 2][c] == player && board[r + 3][c] == player))
                return true;
            if ((r <= ROWS - 4 && c <= COLS - 4) &&
                (board[r][c] == player && board[r + 1][c + 1] == player &&
                    board[r + 2][c + 2] == player && board[r + 3][c + 3] == player))
                return true;
            if ((r >= 3 && c <= COLS - 4) &&
                (board[r][c] == player && board[r - 1][c + 1] == player &&
                    board[r - 2][c + 2] == player && board[r - 3][c + 3] == player))
                return true;
        }
    }
    return false;
}

bool isFull() {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == EMPTY) return false;
    }
    return true;
}

int minimax(int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0 || checkWin(PLAYER) || checkWin(AI) || isFull()) {
        if (checkWin(AI)) return 1000;
        if (checkWin(PLAYER)) return -1000;
        return 0;  // Ничья или продолжение игры
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int col = 0; col < COLS; ++col) {
            if (board[0][col] == EMPTY) {
                std::vector<std::vector<int>> tempBoard = board;
                if (makeMove(col, AI)) {
                    int eval = minimax(depth - 1, false, alpha, beta);
                    board = tempBoard;
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break;
                }
            }
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        for (int col = 0; col < COLS; ++col) {
            if (board[0][col] == EMPTY) {
                std::vector<std::vector<int>> tempBoard = board;
                if (makeMove(col, PLAYER)) {
                    int eval = minimax(depth - 1, true, alpha, beta);
                    board = tempBoard;
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break;
                }
            }
        }
        return minEval;
    }
}

int main() {
    initializeBoard();
    printBoard();
    int turn = PLAYER;
    int selectedCol;

    while (!isFull()) {
        if (turn == PLAYER) {
            std::cout << "Player's turn. Enter column (0-7): ";
            std::cin >> selectedCol;
            if (makeMove(selectedCol, PLAYER)) {
                printBoard();
                if (checkWin(PLAYER)) {
                    std::cout << "Player wins!" << std::endl;
                    break;
                }
                turn = AI;
            }
            else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
        else {
            std::cout << "AI's turn." << std::endl;
            int bestScore = std::numeric_limits<int>::min();
            int bestMove = -1;
            for (int col = 0; col < COLS; ++col) {
                if (board[0][col] == EMPTY) {
                    std::vector<std::vector<int>> tempBoard = board;
                    makeMove(col, AI);
                    int score = minimax(aiDepth, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                    board = tempBoard;
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = col;
                    }
                }
            }
            makeMove(bestMove, AI);
            printBoard();
            if (checkWin(AI)) {
                std::cout << "AI wins!" << std::endl;
                break;
            }
            turn = PLAYER;
        }
    }

    if (isFull() && !checkWin(PLAYER) && !checkWin(AI)) {
        std::cout << "The game is a draw." << std::endl;
    }

    return 0;
}
