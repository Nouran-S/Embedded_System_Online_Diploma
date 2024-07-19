#include <stdio.h>

int main()
{
    char str[100];
    int count = 0;

    printf("Enter a string: ");
    gets(str);

    for (int i = 0; str[i] != 0; i++)
            count++;

    printf("length: %d\n", count);
    return 0;
}
