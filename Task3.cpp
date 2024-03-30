#include <iostream>

const int N = 9;

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }

        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }

            if (j == 8) {
                std::cout << board[i][j];
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool isValid(int board[N][N], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool findEmptyLocation(int board[N][N], int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                return true; // Empty location found
            }
        }
    }
    return false; // No empty location found
}

bool solveSudoku(int board[N][N]) {
    int row, col;
    if (!findEmptyLocation(board, row, col)) {
        return true; // Puzzle solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0; // Backtrack
        }
    }

    return false; // No solution exists
}

int main() {
    int board[N][N];

    std::cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    for (int i = 0; i < N; i++) {
        std::cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < N; j++) {
            std::cin >> board[i][j];
        }
    }

    std::cout << "\nSudoku puzzle:" << std::endl;
    printBoard(board);
    std::cout << std::endl << "Solving..." << std::endl;
    if (solveSudoku(board)) {
        std::cout << "Solution:" << std::endl;
        printBoard(board);
    } else {
        std::cout << "No solution exists" << std::endl;
    }

    return 0;
}
