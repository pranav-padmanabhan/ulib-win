#include "resource.h"

#include <stdio.h>

#ifndef _X86_
#define  _X86_
#endif

#include "uinlineasm.h"

int main(int argc, char *argv[])
{
    int x = 1;
    printf("Before: %d\n", x);

    x = huys::times5(x);

    printf("After : %d\n", x);


    int y = 22;
    printf("Before: %d -- %d\n", x, y);

    huys::swap(&x, &y);

    printf("After : %d -- %d\n", x, y);

    double s = 3.14159/6;

    printf("sine(%lf) = %lf\n", s, huys::sine(s));

    float xx = 2.33f;

    printf("intify(%f) = %d\n", xx, huys::intify(xx));

    float veca[] = {1.0, 2.0, 5.0};
    float vecb[] = {2.0, 3.0, 4.0};

    printf("ScalarProduct %f\n", huys::scalarProduct(veca, vecb, 3));

    printf("rdtsc : %lu \n", huys::rdtsc());

    printf("addf : %.1f + %.1f = %.1f\n", 1.2f, 23.2f, huys::addf(1.2, 23.2));

    getchar();

    return 0;
}

