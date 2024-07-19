#include <stdio.h>
#include <string.h>

void reverseString(char *str, int start, int end);

int main()
{
    char str[100];
    printf("Enter the string: ");
    gets(str);
    printf("Befor: %s\n", str);
    reverseString(str, 0, strlen(str) - 1);
    printf("After: %s\n", str);
    return 0;
}

void reverseString(char *str, int start, int end)
{
    if (start >= end)
        return;

    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    reverseString(str, start + 1, end - 1);
}