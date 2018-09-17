#include <iostream>
#include "SolutionOfTheQuadraticEquation.hpp"

int main() {
  unit_test();
  double a, b, c, x1, x2;
  std::cout << "Enter the a, b, c coefficients of quadratic equation a*x^2 + b*x + c = 0" << std::endl;
  std::cin >> a >> b >> c;
  size_t  n_roots;
  /* Any reason except religion not to make n_roots as a return value? */
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  switch (n_roots) {
    case 0: std::cout << "The quadratic equation has no roots" << std::endl;
      break;

    case 1: std::cout << "The quadratic equation has one root:\n" << "x = " << x1 << std::endl;
      break;

    case 2: std::cout << "The quadratic equation has two roots:\n" << "x1 = " << x1 << " x2 = " << x2 << std::endl;
      break;

    /* It not logical here, try to think of me being a newbie in C, it might make me puzzled for a while, 
       you took n_roots = 3 for the case with infinitely many roots, huh? */
    /* Suggest you elaborating that point, like think about creating some sort of enum or any constatns standing
       for such cases. like EQ_INFINITE_ROOTS (and let's say it is equal to 3, but nobody will get puzzled, coz
       it is somehow hidden, get it? */
    case 3: std::cout << "The quadratic equation has infinitely many roots" << std::endl;
      break;

    default: printf ("main(): ERROR: n_roots = %d\n", n_roots);
      return 1;
  }
}
