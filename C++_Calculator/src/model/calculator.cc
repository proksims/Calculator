#include "calculator.h"

namespace s21 {

// =========================== MAIN FUNCTIONS ======================

int Model::calculator(std::string str, double x) {
  // проверка входных данных
  int err = 0;
  err = check(str, x);

  // парсим строку
  if (err == 0) {
    err = parsing(str, x);
    // пока есть операции в стеке, считаем оставшееся в стеке
    while (!(operation_.empty()) && err == 0) {
      err = counting();
      if (err != 0) {
        break;
      }
    }

    // выводим верхнее посчитанное число в стеке
    if (err == 0) {
      calculator_ = numbers_.top().value;
    }
  }

  return err;
}

double Model::get_calculator() { return calculator_; }

// ============================ CHECK ============================

bool Model::is_operator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

bool Model::is_function(char ch) {
  return (ch == 's' || ch == 'c' || ch == 't' || ch == 'a' || ch == 'l');
}

bool Model::is_letters_in_function(char ch) {
  return (ch == 's' || ch == 'c' || ch == 't' || ch == 'i' || ch == 'o' ||
          ch == 'a' || ch == 'q' || ch == 'l' || ch == 'g');
}

bool Model::is_digit(char ch) { return (ch >= '0' && ch <= '9'); }

int Model::check_brackets(std::string str, int i, int *brackets_open,
                          int *brackets_close) {
  int err = 0;
  char ch = str[i];
  char ch_next =
      str[i + 1];  // не выходит за массив, тк была проверка в check_operation

  if ((ch == '(') && (ch_next == ')')) {
    err = 1;  // ошибка, если 2 скобки подряд
  } else if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') &&
             (ch_next == ')')) {
    err = 1;  // ошибка, если после операции закрывающаяся скобка
  }
  // подсчет скобок
  if (ch == '(') {
    *brackets_open = *brackets_open + 1;
  }
  if (ch == ')') {
    *brackets_close = *brackets_close + 1;
  }
  return err;
}

int Model::check_operation(std::string str, int i, double x) {
  int err = 0;
  int length = str.length();

  // для удобства введем имена переменным
  char ch = str[i];
  char ch_next = str[i + 1];  // не выходит за массив, тк i символ не ch_end
  char ch_start = str.front();
  char ch_end = str.back();

  if (length == 1 && !(is_digit(ch_start))) {
    err = 1;  // ошибка, если в строке только 1 символ
  } else if (ch_start == '*' || ch_start == '/' || ch_start == '^' ||
             ch_start == 'm') {
    err = 1;  // ошибка, если начинается с неправильного символова
  } else if (ch_end == '+' || ch_end == '-' || ch_end == '*' || ch_end == '/' ||
             ch_end == '^' || ch_end == 'd' || ch_end == '(') {
    err = 1;  // ошибка, если заканчивается неправильным символом
  } else if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') &&
             (ch_next == '+' || ch_next == '-' || ch_next == '/' ||
              ch_next == '*' || ch_next == '^') &&
             !(ch == '^' && (ch_next == '+' || ch_next == '-'))) {
    err = 1;  // ошибка, если идут повотряющиеся недопустимые символы
  } else if (ch == '/' && (ch_next == '0' || (ch_next == 'x' && x == 0))) {
    err = 1;  // ошибка, если делим на ноль
  }
  return err;
}

int Model::check(std::string str, double x) {
  int err = 0;
  int brackets_open = 0;
  int brackets_close = 0;
  int length = str.length();

  // проверка длины входной строки
  if (length < 1 || length > 256) {
    err = 1;
  } else {
    // проверка последовательности знаков и скобок
    for (int i = 0; i < length; i++) {
      if (err == 1) {
        break;
      }
      if (err == 0) {
        err = check_operation(str, i, x);
      }
      if (err == 0) {
        err = check_brackets(str, i, &brackets_open, &brackets_close);
      }
    }
    // проверка, что открывающиеся скобоки == закрывающимся
    if (brackets_open != brackets_close) {
      err = 1;
    }
  }
  return err;
}

// =============================== PARSING =============================

double Model::parsing_num(std::string str, int *i) {
  double res = 0.0;
  char str_num[257];
  int j = 0;
  // определим унарный знак
  int sign = 1;  // установим положительный унарный знак
  if (str[*i] == '-') {
    (*i)++;
    sign = -1;
  } else if (str[*i] == '+') {
    (*i)++;
    sign = 1;
  }
  // пойдем по строке определять цифру и записываем ее в str_num
  while ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '.') {
    str_num[j] = str[*i];
    j++;
    (*i)++;
  }
  str_num[j] = '\0';
  res = atof(str_num);  // переводим строку с числами в цифру
  res = res * sign;  // добавляем цифре знак
  return res;
}

char Model::parsing_func(std::string str, int *i) {
  char res = 'f';  // fail если произойдет ошибка
  char str_func[5] = "\0";
  int j = 0;
  while (str[*i] >= 'a' && str[*i] <= 'z') {
    str_func[j] = str[*i];
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
  // если после функции не стоит ( , то выводим ошибку
  if (str[*i] != '(') {
    res = 'f';
  }
  return res;
}

char Model::parsing_mod(std::string str, int *i) {
  char res = 'f';  // fail если произойдет ошибка
  char str_func[3] = "\0";
  int j = 0;
  while (str[*i] >= 'a' && str[*i] <= 'z') {
    str_func[j] = str[*i];
    j++;
    (*i)++;
  }
  str_func[j] = '\0';
  // strcmp == 0, когда содержимое обеих строк равно
  if (!strcmp(str_func, "mod")) {
    res = '%';
  }
  if (str[*i] == '\0') {
    res = 'f';
  }                 // после мод конец строки
  (*i) = (*i) - 1;  // тк, мы двигаем i в основной функции
  return res;
}

void Model::parsing_unar_sign(char ch, int *i) {
  if (ch == '-' || ch == '+') {
    double sign = 1;  // установим положительный унарный знак
    if (ch == '-') {
      (*i)++;
      sign = -1;
    } else if (ch == '+') {
      (*i)++;
      sign = 1;
    }
    // если есть унарный знак добавим (+-1)*
    numbers_.push({'0', sign});  // type = '0'; value = x;
    operation_.push({'*', 0});   // type = '*'; value = 0;
  }
}

int Model::parsing(std::string str, double x) {
  int err = 0;
  int i = 0;  // счетчик для прохода по строке
  char ch_tmp;
  char ch = str[i];           // текущий символ
  char ch_next = str[i + 1];  // следующий символ

  parsing_unar_sign(ch, &i);  // обработаем унарный знак в начале
  int unar_flag = 0;  // унарный счетчик для цикла

  // проходим по всей строке
  while ((ch = str[i]) != '\0') {
    if (ch == ' ' || ch == '\t') {  // пропускаем пробелы
      i++;
      continue;
    }

    if (ch == 'x') {  // парсим x
      unar_flag = 0;
      numbers_.push({'0', x});
      i++;
      continue;
    }

    // парсим числа
    if ((ch >= '0' && ch <= '9') ||
        ((ch == '-' || ch == '+') && unar_flag == 1 && !is_function(ch_next))) {
      unar_flag = 0;  // обнуляем флаг, что унарного знака пока быть не может
      numbers_.push({'0', parsing_num(str, &i)});  // переводим в число
      continue;
    }

    // парсим триг функции и унарный знак для них
    if (is_function(ch) || ((ch == '-' || ch == '+') && unar_flag == 1)) {
      parsing_unar_sign(ch, &i);  // обработаем унарный знак
      unar_flag = 0;  // обновим унарный счетчик для цикла
      ch_tmp = parsing_func(str, &i);
      if (ch_tmp == 'f') {
        err = 1;
        break;
      }
      operation_.push({ch_tmp, 0});
      continue;
    }

    // парсим операторы
    if (((ch == '+' || ch == '-') && unar_flag == 0) || ch == '*' ||
        ch == '/' || ch == '^' || ch == 'm') {
      unar_flag = 0;
      // парсим оператор mod
      if (ch == 'm') {
        unar_flag = 1;
        ch = parsing_mod(str, &i);
        if (ch == 'f') {
          err = 1;
          break;
        }
      }
      if (ch == '^') {
        unar_flag = 1;  //  меняем флаг унарного знака на вкл
      }

      // если стек с операциями пуст
      if (operation_.empty()) {
        operation_.push({ch, 0});
        i++;
        continue;
      }
      // если стек не пуст, и приоритет операции выше, добавляем в стек
      char ch_oper = operation_.top().type;
      if (!operation_.empty() && prior(ch) > prior(ch_oper)) {
        operation_.push({ch, 0});
        i++;
        continue;
      }
      // Если стек не пуст, и приоритет операции ниже, вычисляем
      if (!operation_.empty() && prior(ch) <= prior(ch_oper)) {
        if (counting() == 1) {
          err = 1;
          break;
        }
        if (ch == '%') {
          operation_.push({ch, 0});
          i++;
        }
        continue;
      }
    }

    if (ch == '(') {  // парсим скобочку '('
      unar_flag = 1;
      operation_.push({ch, 0});
      i++;
      continue;
    }
    // парсим скобочку ')' и вычисляем все, что лежало в стеке до '('
    if (ch == ')') {
      while (operation_.top().type != '(') {
        if (counting() == 1) {
          err = 1;
          break;
        } else {
          continue;
        }
      }
      operation_.pop();
      i++;
      continue;
    } else {
      err = 1;  // если ничего не запарсили, то ошибка
      break;
    }
  }
  return err;
}

// =============================== COUNTING =============================
int Model::counting() {
  int err = 0;
  double a = numbers_.top().value;  // достаем первое число
  numbers_.pop();
  char ch_oper = operation_.top().type;  // смотрим на операцию

  if (is_operator(ch_oper) || ch_oper == '%') {
    if (numbers_.empty()) {
      err = 1;
    } else {
      double b = numbers_.top().value;  // достаем второе число
      numbers_.pop();
      switch (ch_oper) {
        case '+':
          numbers_.push({'0', a + b});
          operation_.pop();
          break;
        case '-':
          numbers_.push({'0', b - a});
          operation_.pop();
          break;
        case '^':
          numbers_.push({'0', pow(b, a)});
          operation_.pop();
          break;
        case '*':
          numbers_.push({'0', a * b});
          operation_.pop();
          break;
        case '/':
          numbers_.push({'0', b / a});
          operation_.pop();
          break;
        case '%':
          numbers_.push({'0', fmod(b, a)});
          operation_.pop();
          break;
      }
    }
  } else if (is_letters_in_function(ch_oper)) {
    switch (ch_oper) {
      case 's':
        numbers_.push({'0', sin(a)});
        operation_.pop();
        break;
      case 'c':
        numbers_.push({'0', cos(a)});
        operation_.pop();
        break;
      case 't':
        numbers_.push({'0', tan(a)});
        operation_.pop();
        break;

      case 'i':
        numbers_.push({'0', asin(a)});
        operation_.pop();
        break;
      case 'o':
        numbers_.push({'0', acos(a)});
        operation_.pop();
        break;
      case 'a':
        numbers_.push({'0', atan(a)});
        operation_.pop();
        break;
      case 'q':
        if (a < 0) {
          err = 1;
          break;
        }
        numbers_.push({'0', sqrt(a)});
        operation_.pop();
        break;
      case 'l':
        numbers_.push({'0', log(a)});
        operation_.pop();
        break;
      case 'g':
        numbers_.push({'0', log10(a)});
        operation_.pop();
        break;
    }
  } else {
    err = 1;
  }
  return err;
}

int Model::prior(char ch) {
  int res = -1;
  if (is_letters_in_function(ch)) {
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

// ===============================================================
int Model::credit_calculator(double credit, double deadline, double percent,
                             int type_credit) {
  int err = 0;
  payment_month_ = 0;
  payment_month_min_ = 0;
  payment_month_max_ = 0;
  overpayment_ = 0;
  debt_ = 0;

  if (type_credit == 1) {
    // Аннуитетный платеж

    double perc = (percent / 12 / 100);
    payment_month_ = credit * (((perc)*pow((1 + perc), deadline)) /
                               (pow(1 + perc, deadline) - 1));
    debt_ = payment_month_ * deadline;  // основной долг
    overpayment_ = debt_ - credit;      // переплатили

  } else if (type_credit == 2) {
    // Дифференцированный платеж
    double payment_month_no_persent =
        (credit / deadline);  // месячный платеж без процентов
    double payment_month_persent = 0;  // месячный платеж процентов
    double Q = 0;                      // остаток кредита
    int i = 0;                         // текущий месяц

    for (i = 1; i <= deadline; i++) {
      // считаем проценты каждого месяца, уменьшая общую сумму кретида с помощью
      // основного долга
      Q = (credit - payment_month_no_persent * (i - 1));
      payment_month_persent = Q * percent / 100 / 12;

      // месячный платеж = основной долг + проценты
      payment_month_ = payment_month_no_persent + payment_month_persent;
      if (i == 1) {
        payment_month_max_ = payment_month_;
      }  // первый платеж самый большой
      if (i == deadline) {
        payment_month_min_ = payment_month_;
      }  // последний платеж самый маленький

      // суммируем платежки каждого месяца
      debt_ = debt_ + payment_month_;
    }
    // переплатили
    overpayment_ = debt_ - credit;
  } else {
    err = 1;
  }
  return err;
}

double Model::get_payment_month() { return payment_month_; }
double Model::get_max() { return payment_month_max_; }
double Model::get_min() { return payment_month_min_; }
double Model::get_overpayment() { return overpayment_; }
double Model::get_debt() { return debt_; }

}  // namespace s21
