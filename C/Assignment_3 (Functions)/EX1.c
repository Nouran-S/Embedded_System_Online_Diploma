#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num);
bool printIntervals(int start, int end);

int main()
{
    int intervals[2] = {0};

    printf("Enter the start: ");
    scanf("%d", &intervals[0]);
    printf("Enter the end: ");
    scanf("%d", &intervals[1]);

    printIntervals(intervals[0], intervals[1]);

    return 0;
}

bool isPrime(int num)
{
    if (num <= 1)
        return false;

    if (num % 2 == 0 || num % 3 == 0)
        return false;

    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;

    return true;
}

bool printIntervals(int start, int end)
{
    for (int i = start; i <= end; i++)
        if (isPrime(i))
            printf("%d\t", i);
    printf("\n");
}