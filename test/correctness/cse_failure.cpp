#include <stdio.h>
#include "Halide.h"

using namespace Halide;

int main(int argc, char **argv) {
    Func f("f");

    f() = { 0, 10 };
    Expr cond = f()[0] > f()[1];
    f() = {
        select(cond, 762, 199),
        select(cond, 3, 780)
    };

    int val = evaluate<int>(f()[0]);

    printf("val = %d\n", val);
    printf("Success!\n");
    return 0;
}
