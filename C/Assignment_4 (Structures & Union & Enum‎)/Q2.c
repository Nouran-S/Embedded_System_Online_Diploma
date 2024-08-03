#include <stdio.h>
struct SDistance
{
    int feet;
    float inch;
};

struct SDistance ReadDistance()
{
    struct SDistance temp;
    printf("\n-----------Reading Distance-----------\n");
    printf("Feet: ");
    scanf("%d", &temp.feet);
    printf("Inch: ");
    scanf("%f", &temp.inch);
    return temp;
}

void DisplayDistance(struct SDistance d)
{
    printf("Distance: %d feet, %0.3f inch", d.feet, d.inch);
}

struct SDistance AddDistance(struct SDistance d1, struct SDistance d2)
{
    struct SDistance sum = {0};
    sum.inch = d1.inch + d2.inch;
    while (sum.inch >= 12)
    {
        sum.feet++;
        sum.inch -= 12;
    }

    sum.feet += d1.feet + d2.feet;
    return sum;
}

int main()
{
    struct SDistance d1 = ReadDistance();
    struct SDistance d2 = ReadDistance();
    struct SDistance sum = AddDistance(d1, d2);
    printf("Sum = %d feet, %0.3f inch\n", sum.feet, sum.inch);
    return 0;
}