#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 907

struct driver
{
    char name[50];
    char nationality[35];
    char birthday[20];
    char number[5];
};
typedef struct driver driver;

#define member_size(type, member) (sizeof( ((type *)0)->member ))

driver drivers[N];

// Used to get the pointer location of
// members inside of the driver struct
enum member_sizes {
    NAME = 0,
    NATIONALITY = member_size(driver, name),
    BIRTHDAY = member_size(driver, nationality) + member_size(driver, name),
    NUMBER = member_size(driver, nationality) + member_size(driver, name) + member_size(driver, birthday)
};
typedef enum member_sizes p_locations;

p_locations additions[4] = {NAME, NATIONALITY, BIRTHDAY, NUMBER};


void load_drivers();
int reads_digits(char *number);
char * get_string(char *message, char *s, int size);
void print_drivers(int q);
void bubble_sort(p_locations add);

int main(void)
{
    load_drivers();

    // User input for how to sort
    char sort_crit[3];
    char * m = "How would you like the drivers to be sorted\n1. name\n2. nationality\n3. birthday\n4. driver number\n(enter digit for response)\n";

    get_string(m, sort_crit, 3);
    
    if (sort_crit == NULL)
        return 1;
    
    int crit = reads_digits(sort_crit) - 1;
    if (crit < 0 || crit > 3)
    {
        printf("Choice should be a digit between 1 and 4\n");
        return 2;
    }
    
    p_locations add_to = additions[crit];
    
    bubble_sort(add_to);
    print_drivers(N);

    return 0;
}


void bubble_sort(p_locations add)
{
    // controls the loops through the entire array
    for (int i = 0; i < N; i++)
    {   
        for (int j = 0; j < N - 1; j++)
        {
            
            // swaps if driver[i] is greater than driver 2
            if (strcmp((drivers[j].name + add), (drivers[j + 1].name + add)) > 0)
            {
                driver tmp = drivers[j];
                drivers[j] = drivers[j + 1];
                drivers[j + 1] = tmp;
            }
        }
    }
}
    


char * get_string(char *message, char *s, int size)
{
    printf("%sEnter Response: ", message);   
    char *p = fgets(s, size, stdin);
    if (p == NULL)
    {
        printf("fgets error\n");
        return NULL;
    }

    char *np = strchr(s, '\n');
    if (np == NULL)
    {
        printf("input too long\n");
        return NULL;
    }
    else
    {
        *np = '\0';
    }
    return s;
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

        // Gets the nationality
        strcpy(new.nationality, delimeter);
        delimeter = strtok(NULL, ",");

        // Gets the birthday
        strcpy(new.birthday, delimeter);
        delimeter = strtok(NULL, "\n");

        // Gets the driver number
        // checks for "None" since driver's
        // didn't have numbers before 2014
        strcpy(new.number, delimeter);
        drivers[current_driver] = new;
        current_driver++;

        if (current_driver >= N)
        {
            break;
        }
    }
    return;
}

// Checks if digit then converts to int
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

void print_drivers(int q)
{   


    for (int i = 0; i < q; i++)
    {
        printf("%d. Driver Name: %s\n", i + 1, drivers[i].name);
        printf("Country: %s\n", drivers[i].name + NATIONALITY);
        printf("Birthday: %s\n", drivers[i].name + BIRTHDAY);
        printf("Number: %s\n", drivers[i].name + NUMBER);
    }
}

