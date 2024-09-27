// This file is to test algorithms for the reason that impelemnting code later in python.

#include <iostream>
#include <vector>
#include "solver.h"

int main() {

    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver;

    std::cout << "Solving Sudoku..." << std::endl;

    if (solver.solve(grid)) {
        std::cout << "Solution found:" << std::endl;
        solver.printGrid(grid);
    } else {
        std::cout << "No solution exists!" << std::endl;
    }

    return 0;
}
