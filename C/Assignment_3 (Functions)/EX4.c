#include <stdio.h>

int power(int n, int p);

int main()
{
    int n, p;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("Enter the power: ");
    scanf("%d", &p);
    printf("%d ^ %d = %d\n", n, p, power(n, p));

    return 0;
}

int power(int n, int p)
{
    // 3*3*3
    if (p < 1)
        return 1;

    if (p == 1)
        return n;

    return n * power(n, p - 1);
}