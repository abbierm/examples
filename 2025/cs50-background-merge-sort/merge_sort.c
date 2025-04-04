#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 907
#define R 47

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
driver numbered_drivers[R];

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
void print_drivers(int q, p_locations a, driver darray[]);
void merge_sort(p_locations a, int array_size);
void _merge_sort(p_locations a, int left, int right);
void _merge(p_locations a, int left, int mid, int right, driver darray[]);

int main(void)
{
    
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

    load_drivers();
    if (add_to == NUMBER){
        merge_sort(add_to, R);
        print_drivers(R, add_to, numbered_drivers);
    }
    else {
        merge_sort(add_to, N);
        print_drivers(N, add_to, drivers);
    }

    return 0;
}


void merge_sort(p_locations a, int array_size)
{
    _merge_sort(a, 0, array_size - 1);
}

void _merge_sort(p_locations a, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        // left half
        _merge_sort(a, left, mid);

        // right half
        _merge_sort(a, mid + 1, right);
        
        // mereges different lists depending on if
        // user is sorting via the racing numbers 
        if (a == NUMBER)
            _merge(a, left, mid, right, numbered_drivers);
        else
            _merge(a, left, mid, right, drivers);
    }
    return;
}

void _merge(p_locations a, int left, int mid, int right, driver darray[])
{
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // create two temp arrays to store slices
    driver Left[left_size], Right[right_size];

    // copy data from left chunk to Left
    for (int i = 0; i < left_size; i++)
    {
        Left[i] = darray[i + left];
    }

    // copy data from rigght chunk to Right
    for (int j = 0; j < right_size; j++)
    {
        Right[j] = darray[j + 1 + mid];
    }

    // cursors to keep track of which
    // drivers have been "merged" 
    // already from the temp arrays
    int l = 0, r = 0, cur = left;

    while (l < left_size && r < right_size)
    {
        
        if (strcmp((Left[l].name + a), (Right[r].name + a)) <= 0)
        {
            darray[cur] = Left[l];
            l++;
        }
        else
        {
            darray[cur] = Right[r];
            r++;
        }
        cur++;
    }
    
    // add the rest of Right to drivers array
    while (r < right_size)
    {
        darray[cur] = Right[r];
        cur++;
        r++;
    }
   
    // add the rest of Left to drivers array
    while (l < left_size)
    {
        darray[cur] = Left[l];
        cur++;
        l++;
    }
    
    return;
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
    int stop_value;
    

    fp = fopen("drivers.txt", "r");
    int current_driver = 0, current_number = 0;
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
        strcpy(new.number, delimeter);
        drivers[current_driver] = new;
        current_driver++;

        // adds drivers with numbers to different array
        if (strcmp(delimeter, "0") != 0)
        {
            numbered_drivers[current_number] = new;
            current_number++;
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

void print_drivers(int q, p_locations a, driver darray[])
{   

    for (int i = 0; i < q; i++)
    {
        printf("Driver Name: %s: %s\n", darray[i].name, darray[i].name + a);
    }
}

