/*
 * Project Name: Bank Management System
 * Author: Shad Hossain Fardin
 * Date: 16th June 2025
 */
#include <stdio.h>
#include <string.h>
/*================= Constant =================*/
#define ACCOUNT_FILE "account.dat" // Defines the filename
/*================= Type =================*/
typedef struct
{
    char name[50];   // Account holder's name.
    int account_num; // Unique account number.
    float balance;   // Current account balance.
} Account;
/*================= Function Prototypes =================*/
void flush_input();    // Clears the input buffer.
int menu_selection();  // Displays menu and gets user's choice.
void create_account(); // Creates a new bank account.
void deposit_money();  // Deposits money into an account.
void withdraw_money(); // Withdraws money from an account.
void check_balance();  // Displays the balance of an account.
/*================= Main Function =================*/
int main()
{
    printf("\n-----------------------------------------\n");
    printf("Welcome to Bank Management System!");
    printf("\n-----------------------------------------\n");
    // Main application loop, continues until the user chooses to exit.
    while (1)
    {
        int option = menu_selection(); // Get the user's menu choice.

        switch (option)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit_money();
            break;
        case 3:
            withdraw_money();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            printf("\nClosing the bank. Thanks for your visit.\n");
            return 0; // Exit the program.
        default:
            printf("\nInvalid option! Please try again.\n\n");
            break;
        }
    }
    return 0; // Should not be reached.
}
/*================= Function Definitions =================*/
/**
 * @brief Clears the standard input buffer.
 */
void flush_input()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}
/**
 * @brief Displays the main menu and prompts the user for a selection.
 * @return The integer corresponding to the user's menu choice.
 */
int menu_selection(void)
{
    int option;
    printf("01. Create Account\n");
    printf("02. Deposit Money\n");
    printf("03. Withdraw Money\n");
    printf("04. Check Balance\n");
    printf("05. Exit\n");
    printf("Select your option (1 - 5): ");
    scanf("%d", &option);
    flush_input(); // Clear input buffer

    return option;
}
/**
 * @brief Creates a new bank account and saves it to the account data file.
 */
void create_account()
{
    FILE* file_p = fopen(ACCOUNT_FILE, "ab+"); // Open and create the file in append binary mode with read/write access.
    if (file_p == NULL)
    {
        perror("Error: Unable to open account file"); // perror for detailed error message.
        return;
    }

    Account account;
    printf("Enter your name: ");
    fgets(account.name, sizeof(account.name), stdin);
    account.name[strcspn(account.name, "\n")] = '\0'; // Removes newline

    printf("Enter your account number: ");
    scanf("%d", &account.account_num);
    flush_input(); // Clear input buffer
    account.balance = 0;

    fwrite(&account, sizeof(Account), 1, file_p); // Write account structure to file.
    fclose(file_p);                               // Close file.
    printf("Account created successfully!\n\n");
}
/**
 * @brief Deposits money into an existing bank account.
 */
void deposit_money()
{
    FILE* file_p = fopen(ACCOUNT_FILE, "rb+"); // Opens file in read/write binary mode
    if (file_p == NULL)
    {
        perror("Error: Unable to open account file");
        return;
    }

    Account account;
    int account_num;
    float deposit_amount;

    printf("Enter your account number: ");
    scanf("%d", &account_num);
    printf("Enter the amount to deposit: ");
    scanf("%f", &deposit_amount);
    flush_input(); // Clear input buffer.

    // Reads until end-of-file (EOF).
    while (fread(&account, sizeof(Account), 1, file_p) == 1) // fread() returns number of items read.
    {
        if (account.account_num == account_num)
        {
            account.balance += deposit_amount;                // Update balance.
            fseek(file_p, -(long) sizeof(Account), SEEK_CUR); // Moves file pointer back to the beginning
            fwrite(&account, sizeof(Account), 1, file_p);     // Overwrite old record with updated data.
            fclose(file_p);
            printf("Successfully deposited Tk. %.2f. New balance is Tk. %.2f\n\n", deposit_amount, account.balance);
            return; // Exit
        }
    }
    fclose(file_p);
    printf("Account No: %d was not found.\n\n", account_num); // If account not found.
}
/**
 * @brief Withdraws money from an existing bank account.
 */
void withdraw_money()
{
    FILE* file_p = fopen(ACCOUNT_FILE, "rb+"); // Opens file in read/write binary mode
    if (file_p == NULL)
    {
        perror("Error: Unable to open account file");
        return;
    }

    Account account;
    int account_num;
    float withdraw_amount;

    printf("Enter your account number: ");
    scanf("%d", &account_num);
    printf("Enter the amount to withdraw: ");
    scanf("%f", &withdraw_amount);
    flush_input(); // Clear input buffer.

    // Reads until end-of-file (EOF).
    while (fread(&account, sizeof(Account), 1, file_p) == 1)
    {
        if (account.account_num == account_num)
        {
            if (withdraw_amount > account.balance) // Check for insufficient balance.
            {
                printf("Insufficient balance. Current balance is Tk. %.2f\n\n", account.balance);
                fclose(file_p);
                return; // Exit
            }
            account.balance -= withdraw_amount;               // Deduct withdrawal amount.
            fseek(file_p, -(long) sizeof(Account), SEEK_CUR); // Moves file pointer back to the beginning
            fwrite(&account, sizeof(Account), 1, file_p);     // Overwrite with updated data.
            fclose(file_p);
            printf("Successfully withdrawn Tk. %.2f. New balance is Tk. %.2f\n\n", withdraw_amount, account.balance);
            return; // Exit
        }
    }
    fclose(file_p);
    printf("Account No: %d was not found.\n\n", account_num); // If account not found.
}

/**
 * @brief Checks and displays the balance of an existing bank account.
 */
void check_balance()
{
    FILE* file_p = fopen(ACCOUNT_FILE, "rb"); // Opens file in read-only binary mode
    if (file_p == NULL)
    {
        perror("Error: Unable to open account file");
        return;
    }

    Account account;
    int account_num;

    printf("Enter your account number: ");
    scanf("%d", &account_num);
    flush_input(); // Clear input buffer.

    // Reads until end-of-file (EOF).
    while (fread(&account, sizeof(Account), 1, file_p) == 1)
    {
        if (account.account_num == account_num)
        {
            printf("Your account balance is Tk. %.2f\n\n", account.balance);
            fclose(file_p);
            return; // Exit
        }
    }
    fclose(file_p);
    printf("Account No: %d was not found.\n\n", account_num); // If account not found.
}
