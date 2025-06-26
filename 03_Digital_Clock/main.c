/*
__Project Name: Digital Clock
__Author: Shad Hossain Fardin
__Date: 27th May 2025
*/
#include <stdio.h>
#include <stdlib.h> // for system function
#include <time.h>
#include <unistd.h> // for sleep function
/*=============== Function Prototypes ===============*/
int input_format();
void fill_current_time_date(char*, char*, int);
void clear_screen();
/*======================= Main =======================*/
int main()
{
    printf("\n--------------------------------------------------------------\n");
    printf("\t\tWelcome to the Digital Clock Program!");
    printf("\n--------------------------------------------------------------\n");

    int format_choice = input_format();
    char time_string[50], date_string[100]; // to hold the formatted time and date string
    while (1)
    {
        clear_screen(); // clear the console screen
        fill_current_time_date(time_string, date_string, format_choice);
        printf("\n--------------------------------------------------------------\n");
        printf("\t\t\tDigital Clock");
        printf("\n--------------------------------------------------------------\n");
        printf("Current time: %s\n", time_string);
        printf("Date: %s\n", date_string);
        sleep(1); // sleep for 1 second
    }
    return 0;
}
/*================= Function Definition =================*/
int input_format()
{
    int format;
    printf("\nChoose the time format: ");
    printf("\n1. 24 Hour format");
    printf("\n2. 12 Hour format (default)");
    printf("\nMake a choice (1/2): ");
    scanf("%d", &format);
    return format;
}
void fill_current_time_date(char* buffer_time, char* buffer_date, int format)
{
    time_t raw_time = time(NULL);
    struct tm* current_time = localtime(&raw_time);            // get the current local time
    strftime(buffer_date, 100, "%A, %B %d, %Y", current_time); // format the date
    if (format == 1)                                           // 24-hour format
    {
        strftime(buffer_time, 50, "%H:%M:%S", current_time);
    }
    else // 12-hour format (default)
    {
        strftime(buffer_time, 50, "%I:%M:%S %p", current_time);
    }
}
void clear_screen()
{
// OS based command
#ifdef _WIN32
    system("cls"); // clear screen for Windows
#else
    system("clear"); // clear screen for Unix/Linux
#endif
}
