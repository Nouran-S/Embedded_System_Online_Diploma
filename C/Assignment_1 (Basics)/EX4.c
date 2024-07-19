#include <stdio.h>
int main()
{
    float num;
    printf("Enter A Number: ");
    scanf("%f", &num);
    if(num>0)
        printf("'%0.3f' is positive", num);
    else if (num<0)
        printf("'%0.3f' is negative", num);
    else
        printf("You entered Zero");
    return 0;
}