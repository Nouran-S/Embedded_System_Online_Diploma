#include <stdio.h>

int main()
{
    char arr[26];
    char *ptr = arr;

    for (int i = 0; i < 26; i++)
    {
        *(ptr) = 'A' + i;
        ptr++;
    }

    ptr = arr;
    printf("The Alphabets are... \n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c \t", *ptr);
        ptr++;
    }
    
    return 0;
}