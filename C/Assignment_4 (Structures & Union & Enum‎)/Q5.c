#include <stdio.h>

#define circleArea(r) (3.14 * r * r)

int main()
{
    float r;
    printf(("Enter the redius: "));
    scanf("%f", &r);
    printf("Area = %0.3f\n", circleArea(r));
    return 0;
}