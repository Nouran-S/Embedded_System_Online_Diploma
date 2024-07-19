#include <stdio.h>
int main()
{
    float num[3];
    float max;
    for (int i = 0; i < 3; i++)
    {
        printf("Enter number.%d: ", i+1);
        scanf("%f", &num[i]);
    }

    if (num[0] >= num[1] && num[0] >= num[2])
        max = num[0];
    else if (num[1] >= num[0] && num[1] >= num[2])
        max = num[1];
    else
        max = num[2];

    printf("Largest number is %0.3f\n", max);
    return 0;
}