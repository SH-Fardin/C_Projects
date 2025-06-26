/*
__Project Name: Number Guessing Game
__Author: Shad Hossain Fardin
__Date: 27th May 2025
*/
#include <stdio.h>
#include <stdlib.h> // for rand() and srand()
#include <time.h>   // for seeding

int main()
{
    printf("\n--------------------------------------------------------------\n");
    printf("\t\tWelcome to the Number Guessing Game!");
    printf("\n--------------------------------------------------------------\n");

    int number_to_guess;
    srand(time(NULL));                  // Seed
    number_to_guess = rand() % 100 + 1; // Generate a random number between 1 and 100

    printf("***Try to guess the number I'm thinking of between 1 and 100***\n\n");
    int guess;
    int attempts = 0;
    while (1)
    {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < 1 || guess > 100)
        {
            printf("Please enter a number between 1 and 100.\n\n");
            continue;
        }
        else if (guess < number_to_guess)
        {
            printf("Too low! Try again.\n");
        }
        else if (guess > number_to_guess)
        {
            printf("Too high! Try again.\n");
        }
        else
        {
            printf("Congratulations! You've guessed the number %d in %d attempts.\n\n", number_to_guess, attempts);
            printf("Bye bye :)\n");
            printf("Thank you for playing. I hope you had fun!\n");
            printf("If you want to play again, just run the program again.\n\n");
            printf("***Developed by Shad Hossain Fardin.***\n");
            printf("Exiting...\n");
            return 0;
        }
        printf("\n");
    }

    return 0;
}