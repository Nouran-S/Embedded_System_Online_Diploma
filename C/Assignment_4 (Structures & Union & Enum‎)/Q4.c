#include <stdio.h>
#include <string.h>
struct SStudent
{
    char name[100];
    int rool;
    float marks;
};

struct SStudent ReadStudentData()
{
    struct SStudent temp;
    printf("Enter the student name: ");
    scanf("%s", &temp.name);
    // gets(temp.name);
    printf("Enter the student roll: ");
    scanf("%d", &temp.rool);
    printf("Enter the student marks: ");
    scanf("%f", &temp.marks);
    return temp;
}

void PrintStudentData(struct SStudent temp)
{
    printf("Student name: %s\n", temp.name);
    printf("Student rool: %d\n", temp.rool);
    printf("Student marks: %0.3f\n", temp.marks);
}

int main()
{
    int size = 10;
    struct SStudent students[size];
    for (int i = 0; i < size; i++)
    {
        printf("\n---------Student No.%d-----------\n", i + 1);
        students[i] = ReadStudentData();
    }
    for (int i = 0; i < size; i++)
    {
        printf("\n---------Student No.%d-----------\n", i + 1);
        PrintStudentData(students[i]);
    }
    return 0;
}