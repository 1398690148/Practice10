#include <header1.h>
#include <stdio.h>

void funcA(int x) {
    if (!x) return ;
    printf("funcA : %d\n", x);
    funcB(x - 1);
    return ;
}

void funcB(int x) {
    if (!x) return ;
    printf("funcB : %d\n", x);
    funcA(x - 1);
    return ;
}
