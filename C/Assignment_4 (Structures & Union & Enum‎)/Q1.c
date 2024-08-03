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
    printf("\n----------Reading Data----------\n");
    printf("Enter the student name: ");
    gets(temp.name);
    printf("Enter the student roll: ");
    scanf("%d", &temp.rool);
    printf("Enter the student marks: ");
    scanf("%f", &temp.marks);
    return temp;
}

void PrintStudentData(struct SStudent temp)
{
    printf("\n----------Student Data----------\n");
    printf("Student name: %s\n", temp.name);
    printf("Student rool: %d\n", temp.rool);
    printf("Student marks: %0.3f\n", temp.marks);
}

int main()
{
    struct SStudent student = ReadStudentData();
    PrintStudentData(student);
    return 0;
}