#ifndef SUDOKU_SOLVER_DLX_H
#define SUDOKU_SOLVER_DLX_H

#include <iostream>
#include <vector>
#include <array>

constexpr int SIZE = 9;        // Grid size for standard Sudoku
constexpr int SUBGRID = 3;     // Subgrid size (3x3 in a 9x9 grid)
constexpr int NUM_CONSTRAINTS = 4 * SIZE * SIZE; // Constraints for rows, columns, subgrids, and cell assignment

class DLXNode {
public:
    DLXNode* left;
    DLXNode* right;
    DLXNode* up;
    DLXNode* down;
    DLXNode* column;
    int rowID, columnID;

    DLXNode() : left(this), right(this), up(this), down(this), column(nullptr), rowID(-1), columnID(-1) {}

    void unlinkLR() {
        left->right = right;
        right->left = left;
    }

    void linkLR() {
        left->right = this;
        right->left = this;
    }

    void unlinkUD() {
        up->down = down;
        down->up = up;
    }

    void linkUD() {
        up->down = this;
        down->up = this;
    }
};

class DLX {
private:
    DLXNode* header;
    std::vector<DLXNode*> columnHeaders;
    std::vector<DLXNode*> solution;
    std::vector<std::vector<int>> solutions;  // Store multiple solutions
    int numSolutions;
    bool foundFirstSolution = false;          // Track if the first solution is found

    // Unlink an entire column from the matrix
    void cover(DLXNode* col) {
        col->unlinkLR();
        for (DLXNode* row = col->down; row != col; row = row->down) {
            for (DLXNode* node = row->right; node != row; node = node->right) {
                node->unlinkUD();
            }
        }
    }

    // Relink the column back into the matrix
    void uncover(DLXNode* col) {
        for (DLXNode* row = col->up; row != col; row = row->up) {
            for (DLXNode* node = row->left; node != row; node = node->left) {
                node->linkUD();
            }
        }
        col->linkLR();
    }

    // Solve the Sudoku using DLX recursively
    void search(int depth) {
        if (header->right == header) {
            // Solution found
            recordSolution();
            numSolutions++;
            foundFirstSolution = true;  // Mark that we found the first solution
            return;
        }

        // Choose the column with the least nodes
        DLXNode* col = selectColumn();
        cover(col);

        for (DLXNode* row = col->down; row != col; row = row->down) {
            solution.push_back(row);

            for (DLXNode* node = row->right; node != row; node = node->right) {
                cover(node->column);
            }

            search(depth + 1);

            for (DLXNode* node = solution.back()->left; node != solution.back(); node = node->left) {
                uncover(node->column);
            }

            solution.pop_back();

            // Stop searching after finding the first solution
            if (foundFirstSolution) return;
        }

        uncover(col);
    }

    // Choose the column with the fewest 1s for efficiency
    DLXNode* selectColumn() {
        DLXNode* col = header->right;
        for (DLXNode* temp = header->right; temp != header; temp = temp->right) {
            if (temp->down == temp) continue; // No nodes, skip this column
            if (temp->down->down == temp) return temp; // Column with a single node
        }
        return col;
    }

    // Record the current solution
    void recordSolution() {
        std::vector<int> currentSolution(SIZE * SIZE, 0);
        for (DLXNode* node : solution) {
            int rowID = node->rowID;
            int num = (rowID % SIZE) + 1;
            int cell = rowID / SIZE;
            currentSolution[cell] = num;
        }
        solutions.push_back(currentSolution);
    }

public:
    DLX() : header(new DLXNode()), numSolutions(0) {}

    // Create a sparse matrix for Sudoku constraints
    void createMatrix(const std::vector<std::vector<int>>& grid) {
        // Add column headers for 4 constraints: row, col, subgrid, and cell
        columnHeaders.resize(NUM_CONSTRAINTS);

        for (int i = 0; i < NUM_CONSTRAINTS; ++i) {
            columnHeaders[i] = new DLXNode();
            columnHeaders[i]->column = columnHeaders[i];
            header->left->right = columnHeaders[i];
            columnHeaders[i]->left = header->left;
            columnHeaders[i]->right = header;
            header->left = columnHeaders[i];
        }

        // Add rows representing Sudoku grid and constraints
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (grid[row][col] == 0) {
                    for (int num = 1; num <= SIZE; ++num) {
                        addRow(row, col, num);
                    }
                } else {
                    addRow(row, col, grid[row][col]);
                }
            }
        }
    }

    // Add a row to the matrix representing a possible assignment
    void addRow(int row, int col, int num) {
        int rowConstraint = row * SIZE + num - 1;
        int colConstraint = SIZE * SIZE + col * SIZE + num - 1;
        int subgridConstraint = 2 * SIZE * SIZE + (row / SUBGRID * SUBGRID + col / SUBGRID) * SIZE + num - 1;
        int cellConstraint = 3 * SIZE * SIZE + row * SIZE + col;

        DLXNode* firstNode = nullptr;
        std::array<int, 4> constraints = {rowConstraint, colConstraint, subgridConstraint, cellConstraint};

        for (int constraint : constraints) {
            DLXNode* node = new DLXNode();
            node->rowID = row * SIZE + col;
            node->columnID = constraint;

            DLXNode* colNode = columnHeaders[constraint];
            node->column = colNode;

            if (firstNode == nullptr) {
                firstNode = node;
            }

            // Insert node into the column
            node->up = colNode->up;
            node->down = colNode;
            colNode->up->down = node;
            colNode->up = node;

            // Link nodes together
            node->left = firstNode->left;
            node->right = firstNode;
            firstNode->left->right = node;
            firstNode->left = node;
        }
    }

    // Solve the Sudoku puzzle and stop after finding one solution
    void solveOne() {
        search(0);
    }

    // Print a single Sudoku grid
    void printGrid(const std::vector<int>& grid) const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                std::cout << grid[i * SIZE + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Print only the first solution
    void printOneSolution() {
        if (solutions.empty()) {
            std::cout << "No solutions found." << std::endl;
        } else {
            std::cout << "First Solution:" << std::endl;
            printGrid(solutions[0]);
        }
    }
};

#endif // SUDOKU_SOLVER_DLX_H
