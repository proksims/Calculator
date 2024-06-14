#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../model/calculator.h"

namespace s21 {

class controller {
 public:
  controller(){};
  ~controller(){};

  // калькулятор
  int result_calculator(std::string str, double x) {
    return model_.calculator(str, x);
  }
  double get_result_calculator() { return model_.get_calculator(); }

  // депозитный калькулятор
  int result_credit_calculator(double credit, double deadline, double percent,
                               int type_credit) {
    return model_.credit_calculator(credit, deadline, percent, type_credit);
  }
  double get_result_payment_month() { return model_.get_payment_month(); }
  double get_result_max() { return model_.get_max(); }
  double get_result_min() { return model_.get_min(); }
  double get_result_overpayment() { return model_.get_overpayment(); }
  double get_result_debt() { return model_.get_debt(); }

 private:
  Model model_;
};

}  // namespace s21

#endif
