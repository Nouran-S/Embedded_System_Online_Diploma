#include <stdio.h>
int main()
{
    int n;
    int f = 1;
    printf("Enter A Number: ");
    scanf("%d", &n);

    if (n == 0 || n == 1)
        printf("Factorial = %d\n", f);
    else if (n < 0)
        printf("Error !!\n-ve numbers does not have a factorial \n");
    else
    {
        for (int i = 1; i <= n; i++)
            f *= i;
        printf("Factorial = %d\n", f);
    }
    return 0;
}