#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    char str_rev[100];

    printf("Enter a string: ");
    gets(str);

    for (int i = 0; str[i] != 0; i++)
        str_rev[strlen(str) - i - 1] = str[i];

    printf("STR_Rev: %s", str_rev);
    return 0;
}
