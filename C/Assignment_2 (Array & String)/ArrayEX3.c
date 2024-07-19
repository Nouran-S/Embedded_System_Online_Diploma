#include <stdio.h>

int main()
{
    int x, y;
    printf("Enter No. of rows: ");
    scanf("%d", &x);
    printf("Enter No. of colum: ");
    scanf("%d", &y);

    int arr[x][y];
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            printf("elemet no.%d%d: ", i + 1, j + 1);
            scanf("%d", &arr[i][j]);
        }

    printf("Entered Matrix\n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
            printf("%d \t", arr[i][j]);
        printf("\n");
    }

    printf("Transpose of Matrix\n");
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
            printf("%d \t", arr[j][i]);
        printf("\n");
    }

    return 0;
}
