#include <header1.h>
#include <stdio.h>

void funcC(int a, int b) {
    printf("%d + %d = %d\n", a, b, a + b);
    funcA(a);
    return ;
}
