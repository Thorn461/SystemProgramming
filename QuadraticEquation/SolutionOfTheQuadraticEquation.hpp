#include <cassert>
#include <cmath>
#include <iostream>

/**
 * @function SolveSquare(double a, double b, double c, double *x1, double *x2, size_t *n_roots)
 * @brief Функция для решения квадратных уравнений вида a*x^2 + b*x + c = 0
 * @param [in] a - коэффициент при x^2
 * @param [in] b - коэффициент при x
 * @param [in] c - свободный член
 * @param [out] x1 - указатель на первый корень
 * @param [out] x2 - указатель на второй корень
 * @param [out] n_roots - указатель на количество корней
 * @note Если n_roots равен 3, то это значит, что уравнение имеет бесконечно много корней
 */
void SolveSquare(double a, double b, double c, double *x1, double *x2, size_t *n_roots) {

  assert(std::isfinite (a));
  assert(std::isfinite (b));
  assert(std::isfinite (c));

  assert(x1 != nullptr);
  assert(x2 != nullptr);
  assert(n_roots != nullptr);

  // При a = 0 осстается линейное уравнение b*x + c = 0
  if (a == 0) {
    if (b != 0) {
      *x1 = (-c) / b;
      *n_roots = 1;
      return;
    } else {
      if ( c == 0 ) {
        *n_roots = 3;
        return;
      } else {
        /// Уравнение c = 0 при c <> 0 не имеет решения
        *n_roots = 0;
        return;
      }
    }
  }

  double D = b*b - 4*a*c; // Дискриминант квадратного уравнения a*x^2 + b*x + c = 0

  // D < 0 => корней нет
  if (D < 0) {
    *n_roots = 0;
    return;
  }

  // D = 0 => 1 корень второй кратности
  if (D == 0) {
    *x1 = (-b) / (2 * a);
    *n_roots = 1;
    return;
  }

  // D > 0 => 2 корня
  *x1 = (-b - sqrt(D)) / (2 * a);
  *x2 = (-b + sqrt(D)) / (2 * a);
  *n_roots = 2;
}

void unit_test() {
  double a, b, c, x1, x2;
  size_t n_roots;
  a = 1;
  b = 3;
  c = 2;
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  assert( n_roots == 2 && x1 == -2 && x2 == -1);
  a = 0;
  b = 0;
  c = 0;
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  assert( n_roots == 3 );
  a = 0;
  b = 0;
  c = 1;
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  assert( n_roots == 0 );
  a = 1;
  b = 2;
  c = 1;
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  assert( n_roots == 1 && x1 == -1);
  a = 1;
  b = 2;
  c = 2;
  SolveSquare(a, b, c, &x1, &x2, &n_roots);
  assert( n_roots == 0 );
}

