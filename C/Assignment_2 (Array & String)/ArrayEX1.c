#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // EX: 01
    int x[2][2];
    int y[2][2];
    int z[2][2];
    printf("Enter the elements of the 1st matrix: \n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            printf("element No.%d%d: ", i + 1, j + 1);
            scanf("%d", &x[i][j]);
        }

    printf("Enter the elements of the 2nd matrix: \n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            printf("element No.%d%d: ", i + 1, j + 1);
            scanf("%d", &y[i][j]);
        }

    printf("The Sum: \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
            printf("%d\t", x[i][j] + y[i][j]);
        printf("\n");
    }
    return 0;
}
