#ifndef SRC_MODEL_CALCULATOR_H
#define SRC_MODEL_CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {

typedef struct {
  char type;     // 0 для чисел, + для сложения, - для ...
  double value;  // значение для чисел, для остальных 0
} lexema;

class Model {
 public:
  Model()
      : payment_month_(0),
        payment_month_max_(0),
        payment_month_min_(0),
        overpayment_(0),
        debt_(0),
        calculator_(0){};
  ~Model(){};

  int calculator(std::string str, double x);
  double get_calculator();

  int credit_calculator(double credit, double deadline, double percent,
                        int type_credit);
  double get_payment_month();
  double get_max();
  double get_min();
  double get_overpayment();
  double get_debt();

 private:
  std::stack<lexema> operation_;  // Стек с операциями
  std::stack<lexema> numbers_;    // Стек с числами

  double payment_month_ = 0, payment_month_max_ = 0, payment_month_min_ = 0,
         overpayment_ = 0, debt_ = 0;
  double calculator_ = 0;

  bool is_operator(char ch);
  bool is_function(char ch);
  bool is_letters_in_function(char ch);
  bool is_digit(char ch);

  int check(std::string str, double x);
  int check_operation(std::string str, int i, double x);
  int check_brackets(std::string str, int i, int *brackets_open,
                     int *brackets_close);

  double parsing_num(std::string str, int *i);
  char parsing_func(std::string str, int *i);
  char parsing_mod(std::string str, int *i);
  void parsing_unar_sign(char ch, int *i);
  int parsing(std::string str, double x);

  int counting();
  int prior(char ch);
};

}  // namespace s21

// https://calcus.ru/kreditnyj-kalkulyator

#endif  // SRC_MODEL_CALCULATOR_H
