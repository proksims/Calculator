#include <iostream>

#include "calculator.h"

using std::cin;
using std::cout;
using std::endl;
using namespace s21;

int main() {
  std::string str = "3-2";
  s21::Model model_calc;
  double x = 2;
  int err = model_calc.calculator(str, x);
  std::cout << "start = " << str << std::endl;
  std::cout << "err = " << err << std::endl;
  std::cout << "res = " << model_calc.get_calculator() << std::endl;
  return 0;
}

// int main() {
//   s21::Model model_calc;
//   double type_credit = 2;
//   double credit = 100000.0;
//   double deadline = 24;
//   double percent = 20.0;
//   int err = model_calc.credit_calculator(credit, deadline, percent,
//   type_credit ); std::cout << "err = " << err << std::endl; std::cout <<
//   "платеж = " << model_calc.get_payment_month() << std::endl; std::cout <<
//   "мин = " << model_calc.get_min() << std::endl; std::cout << "мак = " <<
//   model_calc.get_max() << std::endl; std::cout << "проц = " <<
//   model_calc.get_overpayment() << std::endl; std::cout << "долг = " <<
//   model_calc.get_debt() << std::endl;
//   return 0;
// }