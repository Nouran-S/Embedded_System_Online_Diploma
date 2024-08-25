#include <stdio.h>

struct SExmployee
{
    char *name;
    int id;
};


int main()
{
    struct SExmployee emp1 = {"Nouran", 100};
    struct SExmployee emp2 = {"Shrouk", 102};
    struct SExmployee emp3 = {"Israa", 105};
    struct SExmployee *arr[3] = {&emp1, &emp2, &emp3};
    struct SExmployee *(*ptr)[3] = &arr;

    for (int i = 0; i < 3; i++)
    {
        printf("Exmployee No.%d of 3\n", i+1);
        printf("Exmployee ID: %d\n", (**(*ptr + i)).id);
        printf("Exmployee Name: %s\n\n", (**(*ptr + i)).name);
    }

    return 0;
}