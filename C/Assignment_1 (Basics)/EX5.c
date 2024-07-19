#include <stdio.h>
int main()
{
    char num;
    printf("Enter a cahr: ");
    scanf("%c", &num);
    if(num > 64 && num < 123)
        printf("'%c' is a char \n", num);
    else
        printf("'%c' is not a char \n", num);
    return 0;
}