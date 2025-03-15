#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 907

struct driver
{
    char name[50];
    char birth_country[35];
    char birthday[20];
    int driver_number;
    int starts;
    int wins;
    int points;
}
typedef driver;

driver drivers[N];

void load_drivers();
int reads_digits(char * number);
void print_drivers();

int main(void)
{
    load_drivers();
}

// Puts drivers inside of the drivers array
void load_drivers()
{
    FILE *fp;
    char s[1024];
    fp = fopen("drivers.txt", "r");
    int current_driver = 0;
    while (fgets(s, sizeof(s), fp) != NULL)
    {
        driver new;
        char *delimeter = strtok(s, ",");

        // Gets the Name
        strcpy(new.name, delimeter);
        delimeter = strtok(NULL, ",");

        // Gets the country birthplace
        strcpy(new.birth_country, delimeter);
        delimeter = strtok(NULL, ",");

        // Gets the birthday
        strcpy(new.birthday, delimeter);
        delimeter = strtok(NULL, ",");

        // Gets the driver number
        // checks for "None" since driver's
        // didn't have numbers before 2014
        if (strcmp(delimeter, "None") == 0)
        {
            new.driver_number = -1;
        }
        else
        {
            new.driver_number = reads_digits(delimeter);
        }
        delimeter = strtok(NULL, ",");

        // Gets the number of race starts
        new.starts = reads_digits(delimeter);
        delimeter = strtok(NULL, ",");

        // Gets the number of race wins
        new.wins = reads_digits(delimeter);
        delimeter = strtok(NULL, ",\n");

        // Gets the number of total career points
        new.points = reads_digits(delimeter);

        drivers[current_driver] = new;
        current_driver++;
    }
    return;
}


// Converts the text file's digits to integers to create the driver structs
int reads_digits(char* number)
{
    for (int i = 0; i < strlen(number); i++)
    {
        if (!isdigit(number[i]))
        {
            return -1;
        }
    }
    return atoi(number);
}

void print_drivers()
{
    for (int i = 0; i < 100; i++)
    {
        printf("%d. Driver Name: %s\n", i + 1, drivers[i].name);
        printf("Country: %s\n", drivers[i].birth_country);
        printf("Birthday: %s\n", drivers[i].birthday);
        printf("Number: %d\n", drivers[i].driver_number);
        printf("Starts: %d\n", drivers[i].starts);
        printf("Wins: %d\n", drivers[i].wins);
        printf("Points: %d\n\n", drivers[i].points);
    }
}