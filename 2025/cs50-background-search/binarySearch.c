#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define N 58

struct driver
{
    char name[40];
    int number;
}
typedef driver;

driver drivers[N];

bool load_drivers();
void search_drivers(int number, int left, int right);
void print_list();
int get_user_number();

int main(void)
{
    if (!load_drivers())
    {
        return 2;
    }

    printf("Enter driver number: ");
    int x = get_user_number();

    if (x == -1)
    {
        return 3;
    }

    search_drivers(x, 0, N - 1);

    return 0;
}

bool load_drivers()
{
    FILE *fp;
    char s[1024];

    fp = fopen("sorted_f1drivers.txt", "r");
    int current_driver = 0;
    
    while (fgets(s, sizeof(s), fp) != NULL)
    {
        int i = 0;
        driver new;
        char *delimeter = strtok(s, ",");
        while (i < 2)
        {
            if (i == 0 || delimeter == NULL)
            {
                strcpy(new.name, delimeter);
                delimeter = strtok(NULL, "\n");
                i++;
            }
            else if (i == 1)
            {
                for (int j = 0; j < strlen(delimeter); j++)
                {
                    if (!isdigit(delimeter[j]))
                    {
                        printf("Error with car number\n");
                        return false;
                    }
                }
                new.number = atoi(delimeter);
                i++;
            }   
            driver new;
        }
            drivers[current_driver] = new;
            current_driver++;
    }
    return true;
}


void print_list()
{
    for (int i = 0; i < N; i++)
    {
        printf("Driver: %s, Number: %i\n", drivers[i].name, drivers[i].number);
    }
}

int get_user_number()
{
    char input[100];

    char *number = fgets(input, sizeof(input), stdin);
    if (number == NULL)
    {
        printf("invalid\n");
        return -1;
    }
    else
    {
        char *p = strchr(input, '\n');
        if (p == NULL)
        {
            printf("Input too long\n");
            return -1;
        }
        *p = '\0';
    }
    
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            printf("must only enter digits");
            return -1;
        }
    }
    return atoi(input);
}


void search_drivers(int number, int left, int right)
{
    if (right < left)
    {
        printf("No drivers found with number: %d\n", number);
        return;
    }

    int mid = (left + right) / 2;

    if (number == drivers[mid].number)
    {
        printf("Driver: %s\n", drivers[mid].name);
        return;
    }

    else if (number < drivers[mid].number)
    {
        search_drivers(number, left, mid - 1);
    }
    else
    {
        search_drivers(number, mid + 1, right);
    }
}