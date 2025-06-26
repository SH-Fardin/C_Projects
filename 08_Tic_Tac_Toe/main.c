/*
 * Project Name: TIC-TAC-TOE
 * Author: Shad Hossain Fardin
 * Date: 17th June 2025
 */
#include <stdio.h>
#include <stdlib.h> // For system(), srand(), rand()
#include <time.h>   // For time()
/*================= Constant =================*/
#define BOARD_SIZE 3   // Standard 3x3 Tic-Tac-Toe board.
#define PLAYER1 'X'    // For Player 1.
#define PLAYER2 'O'    // For Player 2 (or Computer).
#define EMPTY_CELL ' ' // Representing an empty cell
/*================= Type =================*/
typedef struct
{
    int player1;
    int player2;
    int draw;
} Score;
/*================= Global Variables =================*/
Score score = {.player1 = 0, .player2 = 0, .draw = 0}; // Global score tracker.
char current_player_char;                              // Stores 'X' or 'O' for the current player.
/*================= Function Prototypes =================*/
// Game Setup & Control Functions
int get_game_mode();        // Prompts for game mode
int get_difficulty_level(); // Prompts for AI difficulty
void reset_scoreboard();    // Resets all scores.
// Utility Functions
void clear_screen();       // Clears the console screen.
void exit_message();       // Displays a farewell message.
void clear_input_buffer(); // Clears leftover input from stdin.
// Game Logic Functions
void print_board(char board[BOARD_SIZE][BOARD_SIZE], int mode);              // Prints the board and scoreboard.
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);              // Checks for a win condition.
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);                          // Checks for a draw condition.
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);     // Validates a player's chosen move.
void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player, int mode); // Handles human player input.
void computer_move(char board[BOARD_SIZE][BOARD_SIZE], int difficulty);      // Makes a move for the AI.
void play_game(int mode, int difficulty);                                    // Manages a single round of Tic-Tac-Toe.
/*================= Functions for future implementation (Minimax AI) =================*/
// #define max(a, b) ((a) > (b) ? (a) : (b))
// #define min(a, b) ((a) < (b) ? (a) : (b))
// int evaluate(char board[BOARD_SIZE][BOARD_SIZE]);                                     // Evaluates board state for Minimax.
// int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, int is_maximizing_player); // Minimax algorithm.
// void find_best_move(char board[BOARD_SIZE][BOARD_SIZE], int* row, int* col);          // Finds optimal move using Minimax.
/*================= Main Function =================*/
int main()
{
    srand(time(NULL)); // Seeds a random number

    printf("\n-----------------------------\n");
    printf("Welcome to TIC-TAC-TOE game!!");
    printf("\n-----------------------------\n");

    int current_mode;
    int current_difficulty;
    int prev_mode = -1;       // Tracks previous mode
    int prev_difficulty = -1; // Tracks previous difficulty
    int choice_play_again;

    // Main loop for game mode selection and continuous play sessions.
    while (1)
    {
        current_mode = get_game_mode();

        // Reset scoreboard when game mode changes.
        if (current_mode != prev_mode)
        {
            reset_scoreboard();
            prev_mode = current_mode;
            prev_difficulty = -1; // Difficulty
        }

        if (current_mode == 3)
        { // Exit program.
            break;
        }

        // Handle Single Player mode setup and difficulty selection.
        if (current_mode == 1)
        {
            clear_screen();
            current_difficulty = get_difficulty_level();

            // Reset scoreboard if difficulty changes within Single Player mode.
            if (current_difficulty != prev_difficulty)
            {
                reset_scoreboard();
                prev_difficulty = current_difficulty;
            }

            // Option to return to main mode menu from difficulty selection.
            if (current_difficulty == 3)
            {
                prev_mode = -1; // Force score reset if user re-enters same mode later.
                continue;       // Skip game play, go back to mode selection.
            }
        }
        else // Duo Player mode (current_mode == 2).
        {
            prev_difficulty = -1;    // Difficulty not applicable for Duo mode.
            current_difficulty = -1; // Set to unused value.
        }

        // Loop to play multiple rounds with the same settings.
        do
        {
            play_game(current_mode, current_difficulty);

            printf("Want to play again with same settings? (1 for yes, 0 for no to go to main "
                   "menu): ");
            scanf("%d", &choice_play_again);
            clear_input_buffer(); // Clear input buffer after reading choice.
            clear_screen();
        } while (choice_play_again == 1);
    }

    exit_message(); // Display farewell message before exiting.
    return 0;
}
/*================= Function Definitions =================*/
/**
 * @brief Prompts the user to select the game mode.
 * Ensures valid input (1, 2, or 3).
 * @return The selected game mode.
 */
int get_game_mode()
{
    int mode;
    int input_status;
    do
    {
        printf("\nSelect mode\n");
        printf("01. Single (Play against computer)\n");
        printf("02. Duo (Play with another player)\n");
        printf("03. Exit\n");
        printf("Enter your choice (1 - 3): ");
        input_status = scanf("%d", &mode);
        clear_input_buffer();

        if (input_status != 1 || mode < 1 || mode > 3)
        {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            clear_screen();
        }
    } while (input_status != 1 || mode < 1 || mode > 3);
    return mode;
}
/**
 * @brief Prompts the user to select the AI difficulty level for Single Player mode.
 * @return The selected difficulty level.
 */
int get_difficulty_level()
{
    int difficulty;
    int input_status;
    do
    {
        printf("\nSelect difficulty level\n");
        printf("01. Human (Standard)\n");
        printf("02. God (Impossible to win)\n");
        printf("03. Back to mode menu\n");
        printf("Enter your difficulty (1 - 3): ");
        input_status = scanf("%d", &difficulty);
        clear_input_buffer();

        if (input_status != 1 || difficulty < 1 || difficulty > 3)
        {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            clear_screen();
        }
    } while (input_status != 1 || difficulty < 1 || difficulty > 3);
    return difficulty;
}
/**
 * @brief Resets all scores in the global scoreboard to zero.
 */
void reset_scoreboard()
{
    score.player1 = 0;
    score.player2 = 0;
    score.draw = 0;
}
/**
 * @brief Clears the console screen using system-specific commands.
 */
void clear_screen()
{
#ifdef _WIN32 // For Windows systems.
    system("cls");
#else // For Linux/macOS (Unix-like systems).
    system("clear");
#endif
}
/**
 * @brief Displays a polite farewell message to the user.
 */
void exit_message()
{
    printf("\nBye bye :)\n");
    printf("Thank you for playing. I hope you had fun!\n");
    printf("***Developed by Shad Hossain Fardin.***\n");
    printf("Exiting...\n\n");
}
/**
 * @brief Clears any leftover characters in the standard input buffer.
 * Reads characters until a newline or EOF is encountered.
 */
void clear_input_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
/**
 * @brief Prints the current state of the game board along with the scoreboard.
 * Scoreboard labels adjust based on game mode (Single Player vs. Duo Player).
 * @param board The 2D array representing the Tic-Tac-Toe board.
 * @param mode The current game mode (1 for Single, 2 for Duo).
 */
void print_board(char board[BOARD_SIZE][BOARD_SIZE], int mode)
{
    clear_screen();
    // Print scoreboard based on game mode.
    if (mode == 1)
    { // Single Player mode.
        printf("Score Board:- You (X): %d, Computer (O): %d, Draw: %d\n\n", score.player1, score.player2, score.draw);
    }
    else
    { // Duo Player mode.
        printf("Score Board:- Player-1 (X): %d, Player-2 (O): %d, Draw: %d\n\n", score.player1, score.player2, score.draw);
    }
    // Print the game board grid.
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            printf(" %c ", board[row][col]);
            if (col < BOARD_SIZE - 1)
            {
                printf("|"); // Vertical separator.
            }
        }
        if (row < BOARD_SIZE - 1)
        {
            printf("\n---+---+---\n"); // Horizontal separator.
        }
    }
    printf("\n");
}
/**
 * @brief Checks if a specified player has achieved a winning configuration.
 * @param board The current state of the Tic-Tac-Toe board.
 * @param player The character representing the player ('X' or 'O').
 * @return 1 if the player has won, 0 otherwise.
 */
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    // Check all rows and columns.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1; // Row win.
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1; // Column win.
    }
    // Check main diagonals.
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1; // Primary diagonal.
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1; // Secondary diagonal.

    return 0; // No win detected.
}
/**
 * @brief Checks if the game board is full, indicating a draw.
 * @param board The current state of the Tic-Tac-Toe board.
 * @return 1 if the board is full (draw), 0 otherwise.
 */
int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL)
                return 0; // Empty cell found, not a draw.
        }
    }
    return 1; // Board is full.
}
/**
 * @brief Checks if a player's chosen move (row, col) is valid.
 * @param board The current state of the Tic-Tac-Toe board.
 * @param row The row index (0-based).
 * @param col The column index (0-based).
 * @return 1 if the move is valid, 0 otherwise.
 */
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY_CELL);
}
/**
 * @brief Handles a human player's turn, prompting for and validating input.
 * @param board The game board to update.
 * @param player The current player's character ('X' or 'O').
 * @param mode Game mode, used for turn message.
 */
void player_move(char board[BOARD_SIZE][BOARD_SIZE], char player, int mode)
{
    int row, col;
    int input_status; // Stores scanf's return value for validation.

    do
    {
        // Display turn message based on game mode and current player.
        if (mode == 1)
        {
            printf("\nYour turn.\n");
        }
        else // Duo player mode.
        {
            (current_player_char == PLAYER1) ? printf("\nPlayer-1's turn.\n") : printf("\nPlayer-2's turn.\n");
        }
        printf("Enter row and column (1 - 3) for %c: ", player);
        input_status = scanf("%d %d", &row, &col); // Read user input for row and column.
        clear_input_buffer();                      // Clear any remaining characters in buffer.

        // Convert 1-based input to 0-based array indices.
        row--;
        col--;

        // Validate input: checks if two numbers were read and if the move is valid.
        if (input_status != 2 || !is_valid_move(board, row, col))
        {
            printf("Invalid input or move. Please enter two numbers (1-3) for an empty cell.\n");
        }
    } while (input_status != 2 || !is_valid_move(board, row, col)); // Repeat until valid input/move.
    board[row][col] = player; // Place the player's mark on the board.
}
/**
 * @brief Makes a move for the computer player based on rule-based AI.
 * Prioritizes winning, then blocking, then strategic spots (center/corners for God mode), then any random spot.
 * @param board The game board to update.
 * @param difficulty AI difficulty level.
 */
void computer_move(char board[BOARD_SIZE][BOARD_SIZE], int difficulty)
{
    printf("\nComputer's turn...\n");

    // 1. Check for an immediate winning move.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                board[i][j] = PLAYER2; // Try placing computer's mark.
                if (check_win(board, PLAYER2))
                    return;               // If it wins, make the move and return.
                board[i][j] = EMPTY_CELL; // Undo the trial move.
            }
        }
    }
    // 2. Check for an immediate blocking move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                board[i][j] = PLAYER1; // Try placing opponent's mark.
                if (check_win(board, PLAYER1))
                {
                    board[i][j] = PLAYER2; // Block the opponent's winning move.
                    return;
                }
                board[i][j] = EMPTY_CELL; // Undo the trial move.
            }
        }
    }
    // 3. 'God' difficulty: Prioritize strategic spots (center, then corners).
    if (difficulty == 2)
    {
        if (board[1][1] == EMPTY_CELL) // Center cell move
        {
            board[1][1] = PLAYER2;
            return;
        }
        // List of corner coordinates.
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}
        };
        for (int i = 0; i < 4; i++) // Corner cell move
        {
            if (board[corner[i][0]][corner[i][1]] == EMPTY_CELL)
            {
                board[corner[i][0]][corner[i][1]] = PLAYER2;
                return;
            }
        }
    }
    // 4. Any available move.
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                board[i][j] = PLAYER2;
                return;
            }
        }
    }
}

/**
 * @brief Manages a single round of the Tic-Tac-Toe game.
 * @param mode Game mode (1 for Single Player, 2 for Duo Player).
 * @param difficulty AI difficulty level (relevant for Single Player mode).
 */
void play_game(int mode, int difficulty)
{
    // Initialize the game board with empty cells.
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
        {EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
        {EMPTY_CELL, EMPTY_CELL, EMPTY_CELL},
    };
    current_player_char = (rand() % 2 == 0) ? PLAYER1 : PLAYER2; // Randomly decide who starts.

    print_board(board, mode); // Display the initial empty board.
    // Game loop for a single round.
    while (1)
    {
        // Quality of life feature: Auto-fill if only one empty cell remains.
        int empty_cells_count = 0;
        int last_empty_row = -1, last_empty_col = -1;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == EMPTY_CELL)
                {
                    empty_cells_count++;
                    last_empty_row = i;
                    last_empty_col = j;
                }
            }
        }

        if (empty_cells_count == 1)
        {
            printf("\nOnly one move left! Automatically placing %c at (%d, %d).\n", current_player_char, last_empty_row + 1, last_empty_col + 1);
            board[last_empty_row][last_empty_col] = current_player_char;
        }
        else // Proceed with normal player/AI move.
        {
            if (current_player_char == PLAYER1)
            {
                player_move(board, PLAYER1, mode); // Player 1's turn.
            }
            else // current_player_char == PLAYER2.
            {
                if (mode == 1)
                { // Computer's turn in Single Player mode.
                    computer_move(board, difficulty);
                }
                else
                { // Player 2's turn in Duo Player mode.
                    player_move(board, PLAYER2, mode);
                }
            }
        }
        print_board(board, mode); // Display board after the move.

        // Check for a win after each move.
        if (check_win(board, current_player_char))
        {
            if (current_player_char == PLAYER1)
            {
                score.player1++;
                print_board(board, mode); // Update and show score.
                if (mode == 1)
                    printf("Congratulations!! You (X) have won.\n");
                else
                    printf("Player-1 (X) won!!.\n");
            }
            else
            { // current_player_char == PLAYER2.
                score.player2++;
                print_board(board, mode); // Update and show score.
                if (mode == 1)
                    printf("I (Computer O) won!! Better luck next time.\n");
                else
                    printf("Player-2 (O) won!!.\n");
            }
            break; // End the current game round.
        }
        // Check for a draw if no win.
        if (check_draw(board))
        {
            score.draw++;
            print_board(board, mode); // Update and show score.
            printf("\nIt's a draw.\n");
            break; // End the current game round.
        }
        // Switch turns for the next move.
        current_player_char = (current_player_char == PLAYER1) ? PLAYER2 : PLAYER1;
    }
}
