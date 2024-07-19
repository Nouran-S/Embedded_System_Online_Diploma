#include <stdio.h>

int main()
{
    int size, num, loc = -1;
    printf("Enter No. of elements: ");
    scanf("%d", &size);

    int arr[size];
    for (int i = 0; i < size; i++)
    {
        printf("element no.%d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to be searched: ");
    scanf("%d", &num);

    for (int i = 0; i < size; i++)
        if(num == arr[i])
        {
            loc = i;
            break;
        }

    if(loc == -1)
        printf("%d does not exist\n", num);
    else
        printf("%d found at location: %d\n", num, loc+1);

    return 0;
}
