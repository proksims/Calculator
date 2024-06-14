#ifndef SRC_CALCULATOR_H
#define SRC_CALCULATOR_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================ ПРОВЕРКА ============================
// 1: разные краевые случаи
// 2: если начинается с операций
// 3: если заканчивается операциями
// 4: 2 оператора подряд
// 5: деление на ноль
// 6: проблемы со скобками
// 7: неправильный size
// 8: функц кончается концом строки или хз функция
// 9 мод кончается концом строки
// 10 нет 2 числа для операции
// 11 корень отрицательный

typedef struct {
  char type;     // 0 для чисел, + для сложения, - для ...
  double value;  // значение для чисел, для остальных 0
} lexema;

typedef struct stack {
  lexema value;
  struct stack *next;
} my_stack;
int proverka(char *str, double x);
int proverka_operation(char *str, int i, int end, double x);
int proverka_skobkok(char *str, int i, int *skobkaopen, int *skobkaclose);
void stack_push(my_stack **stack, lexema value);
lexema stack_pop(my_stack **stack);
lexema stack_peek(my_stack **stack);
int stack_size(my_stack **stack);
void stack_free(my_stack **stack);
double parsing_num(char *src, int *i);
char parsing_func(char *src, int *i);
char parsing_mod(char *src, int *i);
int parsing(char *src, my_stack **num, my_stack **operation, double x);
int calculator(char *str, double x, double *result);
int counting(my_stack **num, my_stack **operation, lexema value);
void set_lexema(lexema *result, char type, double value);
int prior(char ch);

// ===================================================================
// https://credistory.ru/blog/annuitetniy-platezh
// https://calcus.ru/kreditnyj-kalkulyator
typedef struct credit_calculator {
  // вход
  double credit;
  double deadline;
  double percent;
  int type_credit;
  // выход
  double payment_month;
  double payment_month_min;
  double payment_month_max;
  double overpayment;
  double debt;
} my_credit_calculator;

int f_credit_calculator(my_credit_calculator *data);

#endif  // SRC_CALCULATOR_H
