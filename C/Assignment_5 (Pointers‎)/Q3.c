#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    printf("Enter a string: ");
    gets(str);
    
    char *p = str;
    for (int i = 0; i < strlen(str); i++)
        p[i] =str[i];
    
    for (int i = strlen(str); i >= 0; i--)
        printf("%c", p[i]);

    printf("\n");
    
    return 0;
}