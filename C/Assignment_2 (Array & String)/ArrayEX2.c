#include <stdio.h>

int main()
{
    int size = 3;
    float sum = 0;
    printf("Enter the number of data: ");
    scanf("%d", &size);

    float numbers[size];
    for (int i = 0; i < size; i++)
    {
        printf("Element No.%d: ", i + 1);
        scanf("%f", &numbers[i]);
        sum += numbers[i];
    }

    printf("Average = %0.3f", sum/size);

    return 0;
}
