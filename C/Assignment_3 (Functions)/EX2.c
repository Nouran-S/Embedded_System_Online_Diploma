#include <stdio.h>
#include <stdbool.h>

int factorial(int num);

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("(%d)! = %d\n", n, factorial(n));

    return 0;
}

int factorial(int num)
{
    if (num < 0)
        return 0;

    else if (num == 1 || num == 0)
        return 1;

    return num * factorial(num - 1);
}