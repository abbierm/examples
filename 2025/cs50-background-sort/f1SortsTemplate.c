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
}
typedef driver;

driver drivers[N];


void load_drivers();
int reads_digits(char *number);
char * get_string(char *message, char *s, int size);
void print_drivers(int q);

int main(void)
{
    load_drivers();


    // User input for how to sort
    char r[3];
    char * m = "How would you like the drivers to be sorted\n1. name\n2. nationality\n3. birthday\n4. driver number\n(enter digit for response)\n";

    get_string(m, r, 3);
    
    if (r == NULL)
    {
        return 1;
    }

    // rc = response choice
    int rc = reads_digits(r);
    if (rc <= 0 || rc > 4)
    {
        printf("Choice should be a digit between 1 and 4\n");
        return 2;
    }

    // User input for direction
    char d[3];
    char *m2 = "Enter order\n1. Ascending\n2. Descending\n(enter either 1 or 2)\n";
    get_string(m2, d, 3);
    if (d == NULL)
    {
        return 1;
    }

    // 'direction choice'
    int dc = reads_digits(d);
    if (dc <= 0 || dc > 2)
    {
        printf("Selection should be a digit between 1 and 2\n");
        return 2;
    }


    return 0;
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
        delimeter = strtok(NULL, "\n");

        drivers[current_driver] = new;
        current_driver++;
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
        printf("Country: %s\n", drivers[i].birth_country);
        printf("Birthday: %s\n", drivers[i].birthday);
        printf("Number: %d\n", drivers[i].driver_number);
    }
}

