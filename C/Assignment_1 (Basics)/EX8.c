#include <stdio.h>
int main()
{
    float x, y, res;
    char operator;

    printf("Enter operator either (+) or (/) or (-) or (*): ");
    scanf("%c", &operator);
    printf("Enter the 1st number: ");
    scanf("%f", &x);
    printf("Enter the 2nd number: ");
    scanf("%f", &y);

    switch (operator)
    {
    case '+':
        res = x + y;
        break;
    case '-':
        res = x - y;
        break;
    case '*':
        res = x * y;
        break;
    case '/':
        res = x / y;
        break;
    }

    printf("%0.3f %c %0.3f = %0.3f\n", x, operator, y, res);

    return 0;
}