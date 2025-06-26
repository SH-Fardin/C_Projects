/*
__Project Name: User Management
__Author: Shad Hossain Fardin
__Date: 15th June 2025
*/
#include <stdio.h>
#include <string.h>
// Platform-specific headers for console I/O
#ifdef _WIN32            // For Windows
    #include <conio.h>   // For _getch()
    #include <windows.h> // Console API for Windows
    #define ENTER_KEY '\r'
#else                    // For Linux/macOS
    #include <termios.h> // For terminal control
    #include <unistd.h>  // For read(), STDIN_FILENO
    #define ENTER_KEY '\n'
#endif
/*================= Constant =================*/
#define CREDENTIAL_LENGTH 30
#define MAX_USER 10
/*================= Type =================*/
typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
} User;
/*================= Global =================*/
User users[MAX_USER];
int user_count = 0;
// Global variables to store original terminal attributes for restoration
#ifdef _WIN32
static HANDLE h_console_input;
static DWORD dw_original_mode;
#else
static struct termios old_termios_settings;
#endif
/*================= Function Prototype =================*/
int menu_selection(void);
void set_terminal_attributes();
void reset_terminal_attributes();
void input_masked_password(char*);
void input_credential(char*, char*); // Input username and password
void register_user();
void login_user();
/*================= Main =================*/
int main()
{
    printf("\n-----------------------------------------\n");
    printf("Welcome to User Management System!");
    printf("\n-----------------------------------------\n");

    while (1)
    {
        int option = menu_selection();

        switch (option)
        {
        case 1:
            register_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            printf("\nExiting program.\n");
            return 0;
        default:
            printf("\nInvalid option!! Please try again.\n\n");
            break;
        }
    }
    return 0;
}
/*================= Function Definition =================*/
/**
 * @brief Displays main menu and gets user's selection.
 * @return The selected option.
 */
int menu_selection(void)
{
    int option;
    printf("01. Register\n");
    printf("02. Login\n");
    printf("03. Exit\n");
    printf("Select your option ( 1 - 3): ");
    scanf("%d", &option);
    getchar(); // Consume newline
    return option;
}
/**
 * @brief Configures terminal for masked password input.
 */
void set_terminal_attributes()
{
#ifdef _WIN32 // Windows-specific
    h_console_input = GetStdHandle(STD_INPUT_HANDLE);
    if (!GetConsoleMode(h_console_input, &dw_original_mode))
    {
        perror("Failed to get console mode");
        return;
    }
    DWORD new_mode = dw_original_mode & (~ENABLE_ECHO_INPUT);
    new_mode |= ENABLE_PROCESSED_INPUT;
    if (!SetConsoleMode(h_console_input, new_mode))
    {
        perror("Failed to set console mode");
        return;
    }
#else // Linux/macOS-specific
    tcgetattr(STDIN_FILENO, &old_termios_settings);
    struct termios new_termios_settings = old_termios_settings;
    new_termios_settings.c_lflag &= (~ECHO & ~ICANON); // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios_settings);
#endif
}
/**
 * @brief Resets terminal attributes to original state.
 */
void reset_terminal_attributes()
{
#ifdef _WIN32 // Windows-specific
    SetConsoleMode(h_console_input, dw_original_mode);
#else // Linux/macOS-specific
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios_settings);
#endif
}
/**
 * @brief Reads password input with masking ('*').
 * @param password Pointer to store the masked password.
 */
void input_masked_password(char* password)
{
    set_terminal_attributes(); // Enable masking

    int i = 0;
    char ch;
    printf("Enter password: ");
    fflush(stdout);

    while (i < CREDENTIAL_LENGTH - 1)
    {
#ifdef _WIN32
        ch = _getch();
#else
        ch = getchar();
#endif
        if (ch == ENTER_KEY)
        {
            if (i == 0)
            {
                printf("\nPassword cannot be empty. Enter a password: ");
                fflush(stdout);
                continue;
            }
            break;
        }
        else if (ch == '\b' || ch == 127) // Backspace or DEL
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); // Erase character from console
                fflush(stdout);
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    password[i] = '\0';

    reset_terminal_attributes(); // Disable masking
    printf("\n");
}
/**
 * @brief Prompts for username and masked password.
 * @param username Pointer to store username.
 * @param password Pointer to store password.
 */
void input_credential(char* username, char* password)
{
    printf("\nEnter username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline
    input_masked_password(password);
}
/**
 * @brief Registers a new user.
 */
void register_user()
{
    if (user_count == MAX_USER)
    {
        printf("Maximum %d users supported. No more registration allowed!!\n", MAX_USER);
        return;
    }

    input_credential(users[user_count].username, users[user_count].password);
    user_count++;

    printf("Registration successful!\n\n");
}
/**
 * @brief Logs in a user.
 */
void login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    input_credential(username, password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            printf("\nLogin successful. Welcome %s!\n\n", users[i].username);
            return;
        }
    }
    printf("Invalid username or password!!! Please try again.\n\n");
}
