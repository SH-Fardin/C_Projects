/*
__Project Name: Simple Calculator
__Author: Shad Hossain Fardin
__Date: 27th May 2025
*/
#include <math.h>
#include <stdio.h>

/*=============== Function Prototypes ===============*/
int menu_selection();
void number_input(double*, double*);
void add();
void subtract();
void multiply();
void divide();
void modulus();

/*======================= Main =======================*/
int main()
{
    printf("\n-----------------------------------------\n");
    printf("Welcome to the Simple Calculator!");
    printf("\n-----------------------------------------\n");

    while (1)
    {
        int option = menu_selection();
        while (getchar() != '\n') // Clear input buffer
            ;
        switch (option)
        {
        case 0:
            printf("\nBye bye :)\n");
            printf("***Developed by Shad Hossain Fardin.***\n");
            printf("Exiting...\n");
            return 0;
        case 1:
            add();
            break;

        case 2:
            subtract();
            break;
        case 3:
            multiply();
            break;
        case 4:
            divide();
            break;
        case 5:
            modulus();
            break;
        default:
            printf("Invalid option, try again.\n");
            break;
        }
        printf("\n-----------------------------------------\n");
        printf("\nAgain, choose your option (0 - 5): ");
        scanf("%d", &option);
        while (getchar() != '\n') // Clear input buffer
            ;
    }
    return 0;
}

/*================= Function Definition =================*/
int menu_selection()
{
    int option;
    printf("***Enter 0 to quit the program***\n");
    printf("Supported options:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("\nNow, please choose your option (0 - 5): ");
    scanf("%d", &option);
}
void number_input(double* a, double* b)
{
    printf("Enter first number: ");
    while (scanf("%lf", a) != 1)
    {
        printf("Invalid input! Enter a number: ");
        while (getchar() != '\n') // Clear input buffer
            ;
    }
    printf("Enter second number: ");
    while (scanf("%lf", b) != 1)
    {
        printf("Invalid input! Enter a number: ");
        while (getchar() != '\n') // Clear input buffer
            ;
    }
}
void add()
{
    double a, b;
    number_input(&a, &b);
    printf("result = %.2f\n", a, b, a + b);
}
void subtract()
{
    double a, b;
    number_input(&a, &b);
    printf("result = %.2f\n", a, b, a - b);
}
void multiply()
{
    double a, b;
    number_input(&a, &b);
    printf("result = %.2f\n", a, b, a * b);
}
void divide()
{
    double a, b;
    number_input(&a, &b);
    if (b == 0)
    {
        printf("Error: Division by zero is not allowed.\n");
    }
    else
    {
        printf("The result of %.2f / %.2f = %.2f\n", a, b, a / b);
    }
}
void modulus()
{
    double a, b;
    number_input(&a, &b);
    if (b == 0)
    {
        printf("Error: Division by zero is not allowed.\n");
    }
    else
    {
        printf("result = %.2f\n", a, b, fmod(a, b));
    }
}
