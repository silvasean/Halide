#include <stdio.h>
#include "Halide.h"

using namespace Halide;

int main(int argc, char **argv) {
    Var x("x");
    Func f("f");

    f(x) = { 10 , 0 };

    // We start at 10 and iterate 5 times, reducing by 1 if > 7.
    // So we should eventually get down to 7.
    RDom r(0, 5);
    Expr a = f(x)[0];
    f(x) = { select(a > 7, a - 1, a), r };

    // If this is unrolled, the program effectively iterates only once.
    f.update(0);
    //f.update(0).unroll(r);

    const int kSize = 1;
    Buffer<int> im = f.realize(kSize)[0];
    for (int i = 0; i < kSize; i++) {
        printf("im(%d) = %d\n", i, im(i));
    }
    if (im(0) != 7) {
      printf("ERROR: Did not get down to 7!\n");
      return 1;
    }

    printf("Success!\n");
    return 0;
}
