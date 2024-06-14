#include "calculator.h"

// int main() {
//   char *tmp = "-3x";
//   double x = 2;
//   double res = 0.0;
//   int err = calculator(tmp, x, &res);
//   printf("err = %d\n", err);
//   printf("res = %lf\n", res);
//   printf("calc = %lf\n", pow(-9, -2));
//   return 0;
// }

// int main() {
//   printf("res = %lf\n", log(10));
//   return 0;
// }

// ============================ ПРОВЕРКА ============================

int proverka_skobkok(char *str, int i, int *skobkaopen, int *skobkaclose) {
  int err = 0;

  if ((str[i] == '(') && (str[i + 1] == ')')) {
    err = 6;
  }
  if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
       str[i] == '^') &&
      (str[i + 1] == ')')) {
    err = 6;
  }
  if (str[i] == '(') {
    *skobkaopen = *skobkaopen + 1;
  }
  if (str[i] == ')') {
    *skobkaclose = *skobkaclose + 1;
  }

  return err;
}
int proverka_operation(char *str, int i, int end, double x) {
  int err = 0;

  if (str[0] == '*' || str[0] == '/' || str[0] == '^' || str[0] == 'm') {
    err = 2;
  }

  else if (str[end] == '+' || str[end] == '-' || str[end] == '*' ||
           str[end] == '/' || str[end] == '^' || str[end] == 'd') {
    err = 3;
  }

  else if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
            str[i] == '^') &&
           (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '/' ||
            str[i + 1] == '*' || str[i + 1] == '^') &&
           !(str[i] == '^' && (str[i + 1] == '+' || str[i + 1] == '-'))) {
    err = 4;  // не будет сеги, тк мы i символ не конечный изза еrr 3, => i+1 не
              // выходит за массив
  } else if (str[i] == '/' &&
             (str[i + 1] == '0' || (str[i + 1] == 'x' && x == 0))) {
    err = 5;  // аналогично err 4
  }

  return err;
}
int proverka(char *str, double x) {
  int err = 0;
  int skobkaopen = 0;
  int skobkaclose = 0;
  int len = strlen(str);
  int end = strlen(str) - 1;

  if (len < 1 || len > 256) {
    err = 7;
  }

  else {
    for (int i = 0; i < len; i++) {
      if (err > 0) {
        break;
      }
      if (err == 0) {
        err = proverka_operation(str, i, end, x);
      }
      if (err == 0) {
        err = proverka_skobkok(str, i, &skobkaopen, &skobkaclose);
      }
      // if (err == 0) check_correct(s, &i);
    }
    if (skobkaopen != skobkaclose) {
      err = 6;
    }
  }
  return err;
}

// ======================= ПАРСИНГ ЧИСЕЛ И СТРОК =======================
double parsing_num(char *src, int *i) {
  double res = 0.0;
  char str_num[256];
  int j = 0;

  int sign = 1;  // positive
  if (src[*i] == '-') {
    (*i)++;
    sign = -1;
  } else if (src[*i] == '+') {
    (*i)++;
    sign = 1;
  }

  while ((src[*i] >= '0' && src[*i] <= '9') || src[*i] == '.') {
    str_num[j] = src[*i];
    j++;
    (*i)++;
  }
  str_num[j] = '\0';
  res = atof(str_num);  // str to num
  res = res * sign;     // add sign

  return res;
}
char parsing_func(char *src, int *i) {
  char res = 'f';  // fail
  char str_func[5] = "\0";
  int j = 0;

  while (src[*i] >= 'a' && src[*i] <= 'z') {
    str_func[j] = src[*i];
    j++;
    (*i)++;
  }
  str_func[j] = '\0';

  // strcmp == 0, когда содержимое обеих строк равно
  if (!strcmp(str_func, "cos")) {
    res = 'c';
  } else if (!strcmp(str_func, "sin")) {
    res = 's';
  } else if (!strcmp(str_func, "tan")) {
    res = 't';
  } else if (!strcmp(str_func, "acos")) {
    res = 'o';
  } else if (!strcmp(str_func, "asin")) {
    res = 'i';
  } else if (!strcmp(str_func, "atan")) {
    res = 'a';
  } else if (!strcmp(str_func, "sqrt")) {
    res = 'q';
  } else if (!strcmp(str_func, "ln")) {
    res = 'l';
  } else if (!strcmp(str_func, "log")) {
    res = 'g';
  }

  if (src[*i] != '(') {
    res = 'f';
  }
  // printf("%c\n", res);
  return res;
}
char parsing_mod(char *src, int *i) {
  char res = 'f';  // fail
  char str_func[3] = "\0";
  int j = 0;

  while (src[*i] >= 'a' && src[*i] <= 'z') {
    str_func[j] = src[*i];
    j++;
    (*i)++;
  }
  str_func[j] = '\0';

  // strcmp == 0, когда содержимое обеих строк равно
  if (!strcmp(str_func, "mod")) {
    res = '%';
  }
  if (src[*i] == '\0') {
    res = 'f';
  }                 // после мод конец строки
  (*i) = (*i) - 1;  // тк, мы двигаем i в основной функции
  return res;
}
int parsing(char *src, my_stack **num, my_stack **operation, double x) {
  int err = 0;
  char ch;
  char ch_tmp;
  int i = 0;
  lexema tmp = {0, 0};
  int unar_sign = 1;  // может быть унарный знак с начала

  if (src[i] == '-' || src[i] == '+') {
    int sign = 1;  // positive
    if (src[i] == '-') {
      i++;
      sign = -1;
    } else if (src[i] == '+') {
      i++;
      sign = 1;
    }
    // если есть унарный знак добавим (-1)*
    set_lexema(&tmp, '0', sign);
    stack_push(num, tmp);
    set_lexema(&tmp, '*', 0);
    stack_push(operation, tmp);
  }
  unar_sign = 0;

  while ((ch = src[i]) != '\0') {
    if (ch == ' ' || ch == '\t') {  // пропускаем пробелы
      i++;
      continue;
    }

    if (ch == 'x') {  // парсим x
      unar_sign = 0;
      set_lexema(&tmp, '0', x);  // tmp.type = '0'; tmp.value = x;
      stack_push(num, tmp);
      i++;
      continue;
    }

    if ((ch >= '0' && ch <= '9') ||
        ((ch == '-' || ch == '+') && unar_sign == 1 &&
         (src[i + 1] != 's' && src[i + 1] != 'c' && src[i + 1] != 't' &&
          src[i + 1] != 'a' && src[i + 1] != 'l'))) {  // парсим числа
      unar_sign = 0;  // обнуляем флаг, что унарного знака пока быть не может
      set_lexema(&tmp, '0', parsing_num(src, &i));  // переводим в число
      stack_push(num, tmp);  // кладем в стек чисел нашу лексему
      continue;
    }

    if ((ch == 's' || ch == 'c' || ch == 't' || ch == 'a' || ch == 'l') ||
        ((ch == '-' || ch == '+') && unar_sign == 1)) {
      if (ch == '-' || ch == '+') {
        int sign = 1;  // positive
        if (ch == '-') {
          i++;
          sign = -1;
        } else if (ch == '+') {
          i++;
          sign = 1;
        }
        // если есть унарный знак перед функцией добавим (-1)*
        set_lexema(&tmp, '0', sign);
        stack_push(num, tmp);
        set_lexema(&tmp, '*', 0);
        stack_push(operation, tmp);
      }

      unar_sign = 0;
      ch_tmp = parsing_func(src, &i);
      if (ch_tmp == 'f') {
        err = 8;
        break;
      }
      set_lexema(&tmp, ch_tmp, 0);
      stack_push(operation, tmp);
      continue;
    }

    if (((ch == '+' || ch == '-') && unar_sign == 0) || ch == '*' ||
        ch == '/' || ch == '^' || ch == 'm') {  // парсим операторы
      unar_sign = 0;

      if (ch == 'm') {
        unar_sign = 1;
        ch = parsing_mod(src, &i);
        // printf("parsing\n");
        // printf("%c\n", ch);
        if (ch == 'f') {
          err = 9;
          break;
        }
      }
      if (ch == '^') {
        unar_sign = 1;
      }

      if (stack_size(operation) == 0) {  // Если стек с операциями пуст
        set_lexema(&tmp, ch, 0);
        stack_push(operation, tmp);  // Операция кладется в стек с операциями
        i++;
        continue;
      }
      char ch_oper = stack_peek(operation).type;
      if (stack_size(operation) != 0 &&
          prior(ch) > prior(ch_oper)) {  // Если стек не пуст, смотрим приоритет
        set_lexema(&tmp, ch, 0);
        stack_push(operation, tmp);
        i++;

        continue;
      }
      if (stack_size(operation) != 0 && prior(ch) <= prior(ch_oper)) {
        if (counting(num, operation, tmp) == 1) {
          err = 1;
          break;
        }
        if (ch == '%') {
          i++;
          set_lexema(&tmp, ch, 0);
          stack_push(operation, tmp);
        }
        continue;
      }
    }

    if (ch == '(') {
      unar_sign = 1;
      set_lexema(&tmp, ch, 0);
      stack_push(operation, tmp);
      i++;
      continue;
    }
    if (ch == ')') {
      while (stack_peek(operation).type != '(') {
        if (counting(num, operation, tmp) == 1) {
          err = 1;
          break;
        } else {
          continue;
        }
      }
      stack_pop(operation);
      i++;
      continue;
    } else {
      err = 1;
      break;
    }
  }
  return err;
}

// =====================================================================
int counting(my_stack **num, my_stack **operation, lexema value) {
  int err = 0;

  // достаем первое число
  double a = stack_peek(num).value;
  stack_pop(num);

  // смотрим на операцию
  char oper = stack_peek(operation).type;

  if (oper == '+' || oper == '-' || oper == '^' || oper == '*' || oper == '/' ||
      oper == '%') {
    if (stack_size(num) == 0) {
      err = 10;
    } else {
      double b = stack_peek(num).value;
      stack_pop(num);
      switch (oper) {
        case '+':
          set_lexema(&value, '0', a + b);
          stack_push(num, value);
          stack_pop(operation);
          break;
        case '-':
          set_lexema(&value, '0', b - a);
          stack_push(num, value);
          stack_pop(operation);
          break;
        case '^':
          set_lexema(&value, '0', pow(b, a));
          stack_push(num, value);
          stack_pop(operation);
          break;
        case '*':
          set_lexema(&value, '0', a * b);
          stack_push(num, value);
          stack_pop(operation);
          break;
        case '/':
          set_lexema(&value, '0', b / a);
          stack_push(num, value);
          stack_pop(operation);
          break;
        case '%':
          set_lexema(&value, '0', fmod(b, a));
          stack_push(num, value);
          stack_pop(operation);
          break;
      }
    }
  } else if (oper == 's' || oper == 'c' || oper == 't' || oper == 'i' ||
             oper == 'o' || oper == 'a' || oper == 'q' || oper == 'l' ||
             oper == 'g') {
    switch (oper) {
      case 's':
        set_lexema(&value, '0', sin(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'c':
        set_lexema(&value, '0', cos(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 't':

        set_lexema(&value, '0', tan(a));
        stack_push(num, value);
        stack_pop(operation);
        break;

      case 'i':
        set_lexema(&value, '0', asin(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'o':
        set_lexema(&value, '0', acos(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'a':
        set_lexema(&value, '0', atan(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'q':
        if (a < 0) {
          err = 11;
          break;
        }
        set_lexema(&value, '0', sqrt(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'l':
        set_lexema(&value, '0', log(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
      case 'g':
        set_lexema(&value, '0', log10(a));
        stack_push(num, value);
        stack_pop(operation);
        break;
    }
  } else {
    err = 1;
  }
  return err;
}
int prior(char ch) {
  int res = -1;
  if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g' || ch == 'i' ||
      ch == 'o' || ch == 'a' || ch == 'q' || ch == 'l') {
    res = 4;
  }
  if (ch == '^') {
    res = 3;
  }
  if (ch == '*' || ch == '/' || ch == '%') {
    res = 2;
  }
  if (ch == '+' || ch == '-') {
    res = 1;
  }
  if (ch == '(' || ch == ')') {
    res = 0;
  }
  return res;
}
void set_lexema(lexema *result, char type, double value) {
  result->type = type;
  result->value = value;
}
int calculator(char *str, double x, double *result) {
  int err = 0;
  err = proverka(str, x);  // проверка входных данных

  if (err == 0) {
    my_stack *num = NULL;        // Стек с числами
    my_stack *operation = NULL;  // Стек с операциями
    err = parsing(str, &num, &operation, x);  // парсим строку

    // пока есть операции в стеке, считаем оставшееся в стеке
    lexema tmp = {0, 0};
    while (stack_size(&operation) != 0 && (err == 0)) {
      err = counting(&num, &operation, tmp);
      if (err != 0) {
        break;
      }
    }

    if (err == 0) {
      *result = stack_peek(&num).value;  // выводим вывод
      // printf("%lf\n", *result);
    }
    stack_free(&num);
    stack_free(&operation);
  }

  return err;
}

// =========================== СТЕК =============================
void stack_push(my_stack **stack, lexema value) {
  my_stack *tmp = malloc(sizeof(my_stack));
  if (tmp) {
    tmp->value = value;
    tmp->next = *stack;  // следующий стек
    *stack = tmp;  // переопределяем указатель стека на новую структуру
  }
}
lexema stack_pop(my_stack **stack) {
  lexema value = {0, 0};
  if (*stack) {
    // переопределим указатель стека, сдвинув его на 1 элемент вперед
    my_stack *out = *stack;
    *stack = (*stack)->next;
    value = out->value;
    free(out);
  }
  return value;
}
lexema stack_peek(my_stack **stack) {
  lexema value = {0, 0};
  value = (*stack)->value;
  return value;
}
int stack_size(my_stack **stack) {
  int size = 0;
  if (*stack) {
    size = 1;
    my_stack *tmp = *stack;
    while (tmp->next != NULL) {
      size++;
      tmp = tmp->next;
    }
  }
  return size;
}
void stack_free(my_stack **stack) {
  if (*stack) {
    my_stack *tmp = *stack;
    while ((*stack)->next != NULL) {
      *stack = (*stack)->next;
      free(tmp);
      tmp = *stack;
    }
    free(tmp);
  }
}

// ===============================================================
int f_credit_calculator(my_credit_calculator *data) {
  int err = 0;
  data->payment_month = 0;
  data->payment_month_min = 0;
  data->payment_month_max = 0;
  data->overpayment = 0;
  data->debt = 0;

  if (data->type_credit == 1) {
    // Аннуитетный платеж

    double perc = (data->percent / 12 / 100);
    data->payment_month =
        data->credit * (((perc)*pow((1 + perc), data->deadline)) /
                        (pow(1 + perc, data->deadline) - 1));
    data->debt = data->payment_month * data->deadline;  // основной долг
    data->overpayment = data->debt - data->credit;  // переплатили

  } else if (data->type_credit == 2) {
    // Дифференцированный платеж
    double payment_month_no_persent =
        (data->credit / data->deadline);  // месячный платеж без процентов
    double payment_month_persent = 0;  // месячный платеж процентов
    double Q = 0;                      // остаток кредита
    int i = 0;                         // текущий месяц

    for (i = 1; i <= data->deadline; i++) {
      // считаем проценты каждого месяца, уменьшая общую сумму кретида с помощью
      // основного долга
      Q = (data->credit - payment_month_no_persent * (i - 1));
      payment_month_persent = Q * data->percent / 100 / 12;

      // месячный платеж = основной долг + проценты
      data->payment_month = payment_month_no_persent + payment_month_persent;
      if (i == 1) {
        data->payment_month_max = data->payment_month;
      }  // первый платеж самый большой
      if (i == data->deadline) {
        data->payment_month_min = data->payment_month;
      }  // последний платеж самый маленький

      // суммируем платежки каждого месяца
      data->debt = data->debt + data->payment_month;
    }
    // переплатили
    data->overpayment = data->debt - data->credit;

  } else {
    err = 1;
  }

  return err;
}

// int main() {
//   my_credit_calculator *A = malloc(1024);

//   A->type_credit = 2;
//   A->credit = 100000.0;
//   A->deadline = 24;
//   A->percent = 20.0;

//   int err = f_credit_calculator(A);
//   printf("err = %d\n", err);
//   printf("платеж = %lf\n", A->payment_month);
//   printf("мин платеж = %lf\n", A->payment_month_min);
//   printf("макс платеж = %lf\n", A->payment_month_max);
//   printf("проценты = %lf\n", A->overpayment);
//   printf("весь долг = %lf\n", A->debt);

//   return 0;
// }
