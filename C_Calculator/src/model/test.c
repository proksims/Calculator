#include <check.h>

#include "calculator.h"

START_TEST(calculator_1) {
  char str[] = "9^-2 * (-9^+2)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = pow(9, -2) * pow(-9, 2);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_2) {
  char str[] = "-(9*9)+ (1/5)-10*(500/2)-3*53-sqrt(8)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig =
      -(9 * 9) + (1.0 / 5.0) - 10.0 * (500.0 / 2.0) - 3.0 * 53.0 - sqrt(8.0);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_3) {
  char str[] = "2mod-3*121mod-2";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = 2 % -3 * 121 % -2;
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_4) {
  char str[] = "(1.2/5.8)-10.2*(500.001/2)-3*53-sqrt(8)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = (1.2 / 5.8) - 10.2 * (500.001 / 2) - 3 * 53 - sqrt(8);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_5) {
  char str[] = "cos(1)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = cos(1);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_6) {
  char str[] = "sin(1) + cos(1) + tan(1) + asin(1)+ acos(1) + atan(1) ";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = sin(1) + cos(1) + tan(1) + asin(1) + acos(1) + atan(1);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_7) {
  char str[] = "sin(0) + cos(0) + tan(0) + asin(0)+ acos(0) + atan(0) ";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = sin(0) + cos(0) + tan(0) + asin(0) + acos(0) + atan(0);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_8) {
  char str[] =
      "sin(0.65) + cos(0.65) + tan(0.65) + asin(0.65)+ acos(0.65) + "
      "atan(0.65) ";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig =
      sin(0.65) + cos(0.65) + tan(0.65) + asin(0.65) + acos(0.65) + atan(0.65);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_9) {
  char str[] = "log(10)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = 1;
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(calculator_10) {
  char str[] = "(sin(8*16)) / sqrt(256)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = (sin(8 * 16)) / sqrt(256);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_11) {
  char str[] = "5.656*(3.111+(2*(3-1.2)))";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = 5.656 * (3.111 + (2 * (3 - 1.2)));
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_12) {
  char str[] = "1+acos(1/2)+5^2";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = 1.0 + acos(1.0 / 2.0) + pow(5.0, 2);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_13) {
  char str[] =
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))";
  double x = 0;
  double res_my = 0.0;
  int err = calculator(str, x, &res_my);
  double res_orig =
      15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
      (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
      (2 + (1 + 1)) *
          (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
           15.23456789101112 / (7.5 - (1 + 1)) * 3.5 - (2 + (1 + 1)));
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_14) {
  char str[] = "sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1)";
  double x = 0;
  double res_my = 0.0;
  int err = calculator(str, x, &res_my);
  double res_orig =
      sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_15) {
  char str[] = "-5*10+5.3*(-5)";
  double x = 0;
  double res_my = 0.0;
  int err = calculator(str, x, &res_my);
  double res_orig = -5 * 10 + 5.3 * (-5);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_16) {
  char str[] = "+sin(x)";
  double x = 2;
  double res_my = 0.0;
  int err = calculator(str, x, &res_my);
  double res_orig = +sin(x);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_17) {
  char str[] = "+8-(-9)+sin(1)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = +8 - (-9) + sin(1);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_18) {
  char str[] = "-cos(1) + 3 + ln(10)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = -cos(1) + 3 + log(10);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_19) {
  char str[] = "7mod2+10";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = 7 % 2 + 10;
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
START_TEST(calculator_20) {
  char str[] = "sqrt(x) + 1/x";
  double res_my = 0.0;
  double x = 2.0;
  int err = calculator(str, x, &res_my);
  double res_orig = sqrt(2.0) + 1.0 / 2.0;
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_21) {
  char str[] = "(2^3^4)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  double res_orig = pow(pow(2, 3), 4);
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
START_TEST(calculator_22) {
  char str[] = "(6+2)/3";
  double x = 0;
  double res_my = 0.0;
  int err = calculator(str, x, &res_my);
  double res_orig = (6.0 + 2) / 3.0;
  ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
  ck_assert_int_eq(0, err);
}
END_TEST
// START_TEST(calculator_) {
//   char str[] = "";
//   double x = 0;
//   double res_my = 0.0;
//   int err = calculator(str, x, &res_my);
//   double res_orig = ;
//   ck_assert_float_eq_tol(res_orig, res_my, 1E-7);
//   ck_assert_int_eq(0, err);
// }
// END_TEST

// 1: разные краевые случаи
START_TEST(err_17) {
  char str[] = "con(2)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(8, err);
}
END_TEST
// 2: если начинается с операций
START_TEST(err_1) {
  char str[] = "*5-9";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(2, err);
}
END_TEST

START_TEST(err_2) {
  char str[] = "/5-9";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(2, err);
}
END_TEST

// 3: если заканчивается операциями
START_TEST(err_3) {
  char str[] = "5-9*";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(3, err);
}
END_TEST
START_TEST(err_4) {
  char str[] = "-5-9-";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(3, err);
}

// 4: 2 оператора подряд
START_TEST(err_5) {
  char str[] = "5*/9";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(4, err);
}
END_TEST
START_TEST(err_6) {
  char str[] = "5+/*9";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(4, err);
}
END_TEST

// 5: деление на ноль
START_TEST(err_7) {
  char str[] = "5.2/0";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(5, err);
}
END_TEST

// 6: проблемы со скобками
START_TEST(err_8) {
  char str[] = "()";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(6, err);
}
END_TEST
START_TEST(err_9) {
  char str[] = "(2-3";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(6, err);
}
END_TEST

// 7: неправильный size
START_TEST(err_10) {
  char str[] =
      "22.2222+0.1000000000-0.10000000000-88.88888888+6.666666666+11.111111111+"
      "333.3333+1111111+4.444444444+7.77777777+8.8888888888+99999999+222222+6+"
      "44444444+1111+2.5555555+1.6666666666+2.33333333333+5.999999+3.666666+7."
      "5555555+555+4.444+1+0.000000+0.222222+0.11111111+0.555555555";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(7, err);
}
END_TEST
START_TEST(err_11) {
  char str[] = "";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(7, err);
}
END_TEST

// 8: функц кончается концом строки или хз функция
START_TEST(err_12) {
  char str[] = "si";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(8, err);
}
END_TEST
START_TEST(err_13) {
  char str[] = "2+3-5-tan";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(8, err);
}
END_TEST
// 9 мод кончается концом строки
START_TEST(err_14) {
  char str[] = "7mod";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(3, err);
}
END_TEST

//
START_TEST(err_15) {
  char str[] = "7-";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(3, err);
}
END_TEST

// 11 корень отрицательный
START_TEST(err_16) {
  char str[] = "sqrt(-9)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(11, err);
}
END_TEST

START_TEST(err_18) {
  char str[] = "12+)";
  double res_my = 0.0;
  double x = 0;
  int err = calculator(str, x, &res_my);
  ck_assert_int_eq(6, err);
}
END_TEST

START_TEST(credit_1) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 100000;
  data->deadline = 24;
  data->percent = 20;
  data->type_credit = 1;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(5089.58, data->payment_month, 1E-1);
  ck_assert_float_eq_tol(22149.92, data->overpayment, 1E-1);
  ck_assert_float_eq_tol(122149.92, data->debt, 1E-1);
  // ck_assert_int_eq(102727, (int)data->payment_month);
  // ck_assert_int_eq(2727, (int)data->overpayment);
  // ck_assert_int_eq(8560, (int)data->debt);
}
END_TEST

START_TEST(credit_2) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 100000;
  data->deadline = 24;
  data->percent = 20;
  data->type_credit = 2;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(4236.11, data->payment_month_min, 1E-1);
  ck_assert_float_eq_tol(5833.33, data->payment_month_max, 1E-1);
  ck_assert_float_eq_tol(20833.33, data->overpayment, 1E-1);
  ck_assert_float_eq_tol(120833.33, data->debt, 1E-1);
}
END_TEST

START_TEST(credit_3) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 1000000;
  data->deadline = 1;
  data->percent = 20;
  data->type_credit = 1;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(1016666.67, data->payment_month, 1E-1);
  ck_assert_float_eq_tol(16666.67, data->overpayment, 1E-1);
  ck_assert_float_eq_tol(1016666.67, data->debt, 1E-1);
  // ck_assert_int_eq(102727, (int)data->payment_month);
  // ck_assert_int_eq(2727, (int)data->overpayment);
  // ck_assert_int_eq(8560, (int)data->debt);
}
END_TEST

START_TEST(credit_4) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 1000000;
  data->deadline = 1;
  data->percent = 20;
  data->type_credit = 2;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(1016666.67, data->payment_month_min, 1E-1);
  ck_assert_float_eq_tol(1016666.67, data->payment_month_max, 1E-1);
  ck_assert_float_eq_tol(16666.67, data->overpayment, 1E-1);
  ck_assert_float_eq_tol(1016666.67, data->debt, 1E-1);
}
END_TEST

START_TEST(credit_5) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 1000000;
  data->deadline = 60;
  data->percent = 20;
  data->type_credit = 1;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(26493.88, data->payment_month, 1E-1);
  // ck_assert_float_eq_tol(589632.80, data->overpayment, 1E-1);
  // ck_assert_float_eq_tol(1589632.80, data->debt, 1E-1);
  // ck_assert_int_eq(26494, (int)data->payment_month);
  ck_assert_int_eq(589633, (int)data->overpayment);
  ck_assert_int_eq(1589633, (int)data->debt);
}
END_TEST

START_TEST(credit_6) {
  my_credit_calculator A = {0};
  my_credit_calculator *data = &A;
  data->credit = 1000000;
  data->deadline = 600;
  data->percent = 20;
  data->type_credit = 2;
  f_credit_calculator(data);
  ck_assert_float_eq_tol(1694.44, data->payment_month_min, 1E-1);
  ck_assert_float_eq_tol(18333.33, data->payment_month_max, 1E-1);
  ck_assert_float_eq_tol(5008333.33, data->overpayment, 1E-1);
  ck_assert_float_eq_tol(6008333.33, data->debt, 1E-1);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("suite_insert");
  TCase *tc_core = tcase_create("insert_tc");

  tcase_add_test(tc_core, calculator_1);
  tcase_add_test(tc_core, calculator_2);
  tcase_add_test(tc_core, calculator_3);
  tcase_add_test(tc_core, calculator_4);
  tcase_add_test(tc_core, calculator_5);
  tcase_add_test(tc_core, calculator_6);
  tcase_add_test(tc_core, calculator_7);
  tcase_add_test(tc_core, calculator_8);
  tcase_add_test(tc_core, calculator_9);
  tcase_add_test(tc_core, calculator_10);
  tcase_add_test(tc_core, calculator_11);
  tcase_add_test(tc_core, calculator_12);
  tcase_add_test(tc_core, calculator_13);
  tcase_add_test(tc_core, calculator_14);
  tcase_add_test(tc_core, calculator_15);
  tcase_add_test(tc_core, calculator_16);
  tcase_add_test(tc_core, calculator_17);
  tcase_add_test(tc_core, calculator_18);
  tcase_add_test(tc_core, calculator_19);
  tcase_add_test(tc_core, calculator_20);
  tcase_add_test(tc_core, calculator_21);
  tcase_add_test(tc_core, calculator_21);
  tcase_add_test(tc_core, calculator_22);

  tcase_add_test(tc_core, err_1);
  tcase_add_test(tc_core, err_2);
  tcase_add_test(tc_core, err_3);
  tcase_add_test(tc_core, err_4);
  tcase_add_test(tc_core, err_5);
  tcase_add_test(tc_core, err_6);
  tcase_add_test(tc_core, err_7);
  tcase_add_test(tc_core, err_8);
  tcase_add_test(tc_core, err_9);
  tcase_add_test(tc_core, err_10);
  tcase_add_test(tc_core, err_11);
  tcase_add_test(tc_core, err_12);
  tcase_add_test(tc_core, err_13);
  tcase_add_test(tc_core, err_14);
  tcase_add_test(tc_core, err_15);
  tcase_add_test(tc_core, err_16);
  tcase_add_test(tc_core, err_17);
  tcase_add_test(tc_core, err_18);

  tcase_add_test(tc_core, credit_1);
  tcase_add_test(tc_core, credit_2);
  tcase_add_test(tc_core, credit_3);
  tcase_add_test(tc_core, credit_4);
  tcase_add_test(tc_core, credit_5);
  tcase_add_test(tc_core, credit_6);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int fail;
  Suite *s;
  SRunner *sr;
  s = suite_insert();
  sr = srunner_create(s);
  fail = srunner_ntests_failed(sr);

  // srunner_run_all(sr, CK_VERBOSE);
  //  srunner_run_all(sr, CK_NORMAL);
  srunner_run_all(sr, CK_ENV);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_free(sr);
  return fail == 0 ? 0 : 1;
}
