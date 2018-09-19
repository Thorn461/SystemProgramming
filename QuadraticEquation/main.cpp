#include <iostream>
#include "SolutionOfTheQuadraticEquation.hpp"

#define  EQ_INFINITE_ROOTS 3

int main() {
  unit_test();
  double a, b, c, x1, x2;
  std::cout << "Enter the a, b, c coefficients of quadratic equation a*x^2 + b*x + c = 0" << std::endl;
  std::cin >> a >> b >> c;
  size_t n_roots = SolveSquare(a, b, c, &x1, &x2);
  switch (n_roots) {
    case 0: std::cout << "The quadratic equation has no roots" << std::endl;
      break;

    case 1: std::cout << "The quadratic equation has one root:\n" << "x = " << x1 << std::endl;
      break;

    case 2: std::cout << "The quadratic equation has two roots:\n" << "x1 = " << x1 << " x2 = " << x2 << std::endl;
      break;

    case EQ_INFINITE_ROOTS: std::cout << "The quadratic equation has infinitely many roots" << std::endl;
      break;

    default: printf("main(): ERROR: n_roots = %d\n", n_roots);
      return 1;
  }
  return 0;
}
