/*
 * Project Name: Sudoku Solver
 * Author: Shad Hossain Fardin
 * Date: 16th June 2025
 */
#include <stdio.h>
/*================= The Puzzle =================*/
// Initial 9x9 Sudoku puzzle. '0' denotes empty cells.
int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};
/*================= Function Prototypes =================*/
void print_puzzle(int[9][9]);                           // Prints the Sudoku grid.
int valid_move(int[9][9], int row, int col, int value); // Checks if a move is valid.
int valid_board(int[9][9]);                             // Validates the initial board.
int solve_puzzle(int[9][9], int row, int col);          // Solves the puzzle using backtracking.
/*================= Main Function =================*/
int main()
{
    printf("\n--------------------------\n");
    printf("Welcome to SUDOKU Solver!");
    printf("\n--------------------------\n");

    printf("\nHere is the puzzle:\n");
    print_puzzle(puzzle);

    // Validate the initial board.
    if (!valid_board(puzzle))
    {
        return 0;
    }
    // Attempt to solve the puzzle.
    if (solve_puzzle(puzzle, 0, 0))
    {
        printf("\nThe puzzle is solved!!\n");
        print_puzzle(puzzle);
    }
    else
    {
        printf("\nThis puzzle is not solvable!!\n");
    }
    return 0;
}
/*================= Function Definition =================*/
/**
 * @brief Prints the 9x9 Sudoku puzzle grid.
 * @param puzzle The 2D array representing the Sudoku puzzle.
 */
void print_puzzle(int puzzle[9][9])
{
    printf("+-------+-------+-------+\n");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("|-------+-------+-------|\n");
        }
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("| ");
            }
            // Print empty space for '0', otherwise the number.
            if (puzzle[row][col] == 0)
            {
                printf("  ");
            }
            else
            {
                printf("%d ", puzzle[row][col]);
            }
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}
/**
 * @brief Checks if a 'value' is valid at (row, col) following Sudoku rules.
 * @param puzzle The current Sudoku puzzle.
 * @param row The row index.
 * @param col The column index.
 * @param value The number to check.
 * @return 1 if valid, 0 otherwise.
 */
int valid_move(int puzzle[9][9], int row, int col, int value)
{
    // Check row and column.
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == value)
            return 0;
        if (puzzle[i][col] == value)
            return 0;
    }
    // Check 3x3 subgrid.
    int subgrid_start_row = row - row % 3;
    int subgrid_start_col = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[subgrid_start_row + i][subgrid_start_col + j] == value)
            {
                return 0;
            }
        }
    }
    return 1;
}
/**
 * @brief Checks if the initial Sudoku board is valid.
 * @param puzzle The initial Sudoku puzzle.
 * @return 1 if valid, 0 if violations exist.
 */
int valid_board(int puzzle[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (puzzle[row][col] != 0)
            {
                int value_to_check = puzzle[row][col];
                puzzle[row][col] = 0; // Temporarily clear.

                if (!valid_move(puzzle, row, col, value_to_check))
                {
                    puzzle[row][col] = value_to_check; // Restore.
                    printf("\nInvalid puzzle provided!!\n");
                    return 0;
                }
                puzzle[row][col] = value_to_check; // Restore.
            }
        }
    }
    return 1;
}
/**
 * @brief Solves the Sudoku puzzle.
 * @param puzzle The Sudoku puzzle to solve (modified in place).
 * @param row The current row.
 * @param col The current column.
 * @return 1 if solved, 0 if unsolvable.
 */
int solve_puzzle(int puzzle[9][9], int row, int col)
{
    // Adjust coordinates for next cell.
    if (col == 9)
    {
        row++;
        col = 0;
    }
    // Base case: All cells processed.
    if (row == 9)
    {
        return 1;
    }
    // If cell is pre-filled, move to next.
    if (puzzle[row][col] > 0)
    {
        return solve_puzzle(puzzle, row, col + 1);
    }
    // Try numbers 1-9 in the current empty cell.
    for (int i = 1; i <= 9; i++)
    {
        if (valid_move(puzzle, row, col, i))
        {
            puzzle[row][col] = i; // Place number.
            if (solve_puzzle(puzzle, row, col + 1))
            {
                return 1; // If successful.
            }
            puzzle[row][col] = 0; // Backtrack: Reset cell if path fails.
        }
    }
    return 0; // No valid number found for this cell.
}
