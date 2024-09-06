#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <iostream>

class SudokuSolver {
public:
    // Constructor
    SudokuSolver() {}

    // Function to solve the Sudoku puzzle using backtracking
    bool solve(std::vector<std::vector<int>>& grid) {
        int row, col;

        // If no empty cell is found, the puzzle is solved
        if (!findEmptyCell(grid, row, col)) {
            return true;  // Puzzle solved
        }

        // Try placing digits 1 to 9 in the empty cell
        for (int num = 1; num <= 9; ++num) {
            // Check if the current number can be placed
            if (isValid(grid, row, col, num)) {
                // Place the number
                grid[row][col] = num;

                // Recursively try to solve the rest of the grid
                if (solve(grid)) {
                    return true;
                }

                // If the solution doesn't work, backtrack by removing the number
                grid[row][col] = 0;
            }
        }

        // If no number works, return false (triggering backtracking)
        return false;
    }

    // Utility function to print the Sudoku grid
    void printGrid(const std::vector<std::vector<int>>& grid) {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                std::cout << grid[row][col] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    // Helper function to check if a number can be placed in the given cell
    bool isValid(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
        // Check the row
        for (int i = 0; i < 9; ++i) {
            if (grid[row][i] == num) {
                return false;
            }
        }

        // Check the column
        for (int i = 0; i < 9; ++i) {
            if (grid[i][col] == num) {
                return false;
            }
        }

        // Check the 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }

        // The number can be placed
        return true;
    }

    // Helper function to find the next empty cell (indicated by a 0)
    bool findEmptyCell(const std::vector<std::vector<int>>& grid, int& row, int& col) {
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++col) {
                if (grid[row][col] == 0) {
                    return true;  // Found an empty cell
                }
            }
        }
        return false;  // No empty cells left
    }
};

#endif // SOLVER_H
