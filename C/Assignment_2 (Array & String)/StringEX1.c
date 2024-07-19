#include <stdio.h>

int main()
{
    char str[100];
    char ch;
    int count = 0;

    printf("Enter a string: ");
    gets(str);
    printf("Enter a char: ");
    scanf("%c", &ch);

    for (int i = 0; str[i] != 0; i++)
        if(str[i] == ch)
            count++;

    printf("freq of (%c): %d\n", ch, count);

    return 0;
}
