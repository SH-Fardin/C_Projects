/*
__Project Name: Progress Bar
__Author: Shad Hossain Fardin
__Date: 28th May 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*================= Constant =================*/
#define MAX_BAR_LENGTH 100
#define TASK_NUMBER 5
/*================= Type =================*/
typedef struct
{
    int id;
    int bar_step; // progress speed
    int progress; // progress in percentage
} Task;
/*================= Function Prototypes =================*/
void print_pogress_bar(Task tasks);
void input_structure(Task tasks[]);
void clear_screen();
void run_progress_simulation(Task tasks[]);
/*================= Main =================*/
int main()
{
    srand(time(NULL)); // seed generator
    Task tasks[TASK_NUMBER];
    input_structure(tasks);
    run_progress_simulation(tasks);

    return 0;
}
/*================= Function Definition =================*/
void print_pogress_bar(Task tasks)
{
    int bar_to_show = (tasks.progress * MAX_BAR_LENGTH) / 100;
    printf("Task %d: [", tasks.id);
    for (int i = 0; i < MAX_BAR_LENGTH; i++)
    {
        if (i < bar_to_show)
        {
            printf("=");
        }
        else
        {
            printf(" ");
        }
    }
    printf("] %3d%%\n", tasks.progress);
}
void input_structure(Task tasks[])
{
    for (int i = 0; i < TASK_NUMBER; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].bar_step = rand() % 5 + 1;
        tasks[i].progress = 0;
    }
}
void clear_screen()
{
#ifdef _WIN32
    system("cls"); // clear screen for Windows
#else
    system("clear"); // clear screen for Unix/Linux
#endif
}
void run_progress_simulation(Task tasks[])
{
    int task_incomplete = 1;
    while (task_incomplete)
    {
        task_incomplete = 0;
        clear_screen();
        for (int i = 0; i < TASK_NUMBER; i++)
        {
            tasks[i].progress += tasks[i].bar_step;

            if (tasks[i].progress > 100)
            {
                tasks[i].progress = 100;
            }

            if (tasks[i].progress < 100)
            {
                task_incomplete = 1;
            }
            print_pogress_bar(tasks[i]);
        }
        sleep(1); // sleep for 1 second
    }
    printf("All task completed!!");
}
