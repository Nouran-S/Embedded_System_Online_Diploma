#include <stdio.h>
struct SComplex
{
    float reel;
    float imag;
};

struct SComplex ReadComplex()
{
    struct SComplex temp;
    printf("\n-----------Reading Complex-----------\n");
    printf("Real: ");
    scanf("%f", &temp.reel);
    printf("Imag: ");
    scanf("%f", &temp.imag);
    return temp;
}

void DisplayComplex(struct SComplex n)
{
    printf("Complex: (%0.3f)+(%0.3f)J", n.reel, n.imag);
}

struct SComplex AddComplex(struct SComplex d1, struct SComplex d2)
{
    struct SComplex sum = {0};
    sum.reel += d1.reel + d2.reel;
    sum.imag += d1.imag + d2.imag;
    return sum;
}

int main()
{
    struct SComplex d1 = ReadComplex();
    struct SComplex d2 = ReadComplex();
    struct SComplex sum = AddComplex(d1, d2);
    DisplayComplex(sum);
    return 0;
}