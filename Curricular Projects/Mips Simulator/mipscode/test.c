#include "io.h"

// this function computes the Ackermann function A(m,n).
// A(0,n) = n + 1
// A(m,0) = A(m-1,1) for m > 0
// A(m,n) = A(m-1,A(m,n-1)) for m > 0 and n > 0
int ackermann(int m)
{
    return m;
}

int main()
{
  int m = 3;
  mips_print_int(ackermann(m));

  return 0;
}

