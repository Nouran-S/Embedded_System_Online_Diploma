#include <stdio.h>

int main()
{
    int size, num, loc;
    printf("Enter No. of elements: ");
    scanf("%d", &size);

    int arr[size];
    int arr_temp[size+1];
    for (int i = 0; i < size; i++)
    {
        printf("element no.%d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to be inserted: ");
    scanf("%d", &num);
    printf("Enter the location: ");
    scanf("%d", &loc);

    for (int i = 0; i <loc-1; i++)
            arr_temp[i] = arr[i];
    arr_temp[loc-1] = num;
    for (int i = loc; i <= size; i++)
        arr_temp[i] = arr[i-1];

    for (int i = 0; i < size; i++)
        printf("%d\t", arr[i]);
    printf("\n");
    for (int i = 0; i < size+1; i++)
        printf("%d\t", arr_temp[i]);

    return 0;
}
