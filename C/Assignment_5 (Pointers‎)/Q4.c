#include <stdio.h>

int main()
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *ptr = &arr[9];

    for (int i = 9; i >=0; i--)
    {
        printf("%d \t", *ptr);
        ptr--;
    }

    printf("\n");
    
    return 0;
}