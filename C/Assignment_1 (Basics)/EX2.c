#include <stdio.h>
int main()
{
    char x;
    printf("Enter an alphabet: ");
    scanf("%c", &x);
    switch (x)
    {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'U':
    case 'u':
        printf("'%c' is a vowel", x);
        break;

    default:
        printf("'%c' is a constant", x);
    }

    return 0;
}