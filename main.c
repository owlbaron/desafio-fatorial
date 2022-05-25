#include <stdio.h>
#include "tinyexpr.h"

int main(int argc, char *argv[]) {
  double answer;
  const char *expr = "(5 + 2)!";

  answer = te_interp(expr, 0);
  printf("The expression:\n\t%s\nevaluates to:\n\t%f\n", expr, answer);
  return 0;
}
