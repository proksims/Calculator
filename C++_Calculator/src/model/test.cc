#include "calculator.h"
#include "gtest/gtest.h"

s21::Model model_calc;

TEST(Calculator, calculator_1) {
  std::string str = "9^-2 * (-9^+2)";
  double x = 2;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = pow(9, -2) * pow(-9, 2);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_2) {
  std::string str = "-(9*9)+ (1/5)-10*(500/2)-3*53-sqrt(8)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig =
      -(9 * 9) + (1.0 / 5.0) - 10.0 * (500.0 / 2.0) - 3.0 * 53.0 - sqrt(8.0);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_3) {
  std::string str = "2mod-3*121mod-2";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = 2 % -3 * 121 % -2;
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_4) {
  std::string str = "(1.2/5.8)-10.2*(500.001/2)-3*53-sqrt(8)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();

  double res_orig = (1.2 / 5.8) - 10.2 * (500.001 / 2) - 3 * 53 - sqrt(8);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_5) {
  std::string str = "cos(1)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = cos(1);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_6) {
  std::string str = "sin(1) + cos(1) + tan(1) + asin(1)+ acos(1) + atan(1) ";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = sin(1) + cos(1) + tan(1) + asin(1) + acos(1) + atan(1);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_7) {
  std::string str = "sin(0) + cos(0) + tan(0) + asin(0)+ acos(0) + atan(0) ";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = sin(0) + cos(0) + tan(0) + asin(0) + acos(0) + atan(0);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_8) {
  std::string str =
      "sin(0.65) + cos(0.65) + tan(0.65) + asin(0.65)+ acos(0.65) + "
      "atan(0.65) ";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig =
      sin(0.65) + cos(0.65) + tan(0.65) + asin(0.65) + acos(0.65) + atan(0.65);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_9) {
  std::string str = "log(10)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = 1;
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_10) {
  std::string str = "(sin(8*16)) / sqrt(256)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = (sin(8 * 16)) / sqrt(256);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_11) {
  std::string str = "5.656*(3.111+(2*(3-1.2)))";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = 5.656 * (3.111 + (2 * (3 - 1.2)));
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_12) {
  std::string str = "1+acos(1/2)+5^2";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = 1.0 + acos(1.0 / 2.0) + pow(5.0, 2);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_13) {
  std::string str =
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig =
      15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
      (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
      (2 + (1 + 1)) *
          (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
           15.23456789101112 / (7.5 - (1 + 1)) * 3.5 - (2 + (1 + 1)));
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_14) {
  std::string str =
      "sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig =
      sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_15) {
  std::string str = "-5*10+5.3*(-5)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = -5 * 10 + 5.3 * (-5);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_16) {
  std::string str = "+sin(x)";
  double x = 2;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = +sin(x);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_17) {
  std::string str = "+8-(-9)+sin(1)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = +8 - (-9) + sin(1);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_18) {
  std::string str = "-cos(1) + 3 + ln(10)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = -cos(1) + 3 + log(10);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_19) {
  std::string str = "7mod2+10";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = 7 % 2 + 10;
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_20) {
  std::string str = "sqrt(x) + 1/x";
  double x = 2.0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = sqrt(2.0) + 1.0 / 2.0;
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_21) {
  std::string str = "(2^3^4)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = pow(pow(2, 3), 4);
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

TEST(Calculator, calculator_22) {
  std::string str = "(6+2)/3";
  double x = 0;
  int err = model_calc.calculator(str, x);
  double res_my = model_calc.get_calculator();
  double res_orig = (6.0 + 2) / 3.0;
  ASSERT_NEAR(res_my, res_orig, 1e-6);
  EXPECT_EQ(err, 0);
}

// =============================================================
// 1: разные краевые случаи
TEST(Calculator, err_0) {
  std::string str = "con(2)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 2: если начинается с операций
TEST(Calculator, err_1) {
  std::string str = "*5-9";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_2) {
  std::string str = "/5-9";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 3: если заканчивается операциями
TEST(Calculator, err_3) {
  std::string str = "5-9*";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_4) {
  std::string str = "-5-9-";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 4: 2 оператора подряд
TEST(Calculator, err_5) {
  std::string str = "5*/9";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_6) {
  std::string str = "5+/*9";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 5: деление на ноль
TEST(Calculator, err_7) {
  std::string str = "5.2/0";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 6: проблемы со скобками
TEST(Calculator, err_8) {
  std::string str = "()";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_9) {
  std::string str = "(2-3";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 7: неправильный size
TEST(Calculator, err_10) {
  std::string str =
      "22.2222+0.1000000000-0.10000000000-88.88888888+6.666666666+11.111111111+"
      "333.3333+1111111+4.444444444+7.77777777+8.8888888888+99999999+222222+6+"
      "44444444+1111+2.5555555+1.6666666666+2.33333333333+5.999999+3.666666+7."
      "5555555+555+4.444+1+0.000000+0.222222+0.11111111+0.555555555";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_11) {
  std::string str = "";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 8: функц кончается концом строки или хз функция
TEST(Calculator, err_12) {
  std::string str = "si";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_13) {
  std::string str = "2+3-5-tan";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 9 мод кончается концом строки
TEST(Calculator, err_14) {
  std::string str = "7mod";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

//
TEST(Calculator, err_15) {
  std::string str = "7-";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// 11 корень отрицательный
TEST(Calculator, err_16) {
  std::string str = "sqrt(-9)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

TEST(Calculator, err_17) {
  std::string str = "12+)";
  double x = 0;
  int err = model_calc.calculator(str, x);
  EXPECT_EQ(1, err);
}

// =============================================================
TEST(Calculator, credit_1) {
  double credit = 100000;
  double deadline = 24;
  double percent = 20;
  int type_credit = 1;
  int err =
      model_calc.credit_calculator(credit, deadline, percent, type_credit);
  ASSERT_NEAR(5089.58, model_calc.get_payment_month(), 1E-1);
  ASSERT_NEAR(22149.92, model_calc.get_overpayment(), 1E-1);
  ASSERT_NEAR(122149.92, model_calc.get_debt(), 1E-1);
  EXPECT_EQ(0, err);
}

TEST(Calculator, credit_2) {
  double credit = 100000;
  double deadline = 24;
  double percent = 20;
  int type_credit = 2;
  int err =
      model_calc.credit_calculator(credit, deadline, percent, type_credit);
  ASSERT_NEAR(4236.11, model_calc.get_min(), 1E-1);
  ASSERT_NEAR(5833.33, model_calc.get_max(), 1E-1);
  ASSERT_NEAR(20833.33, model_calc.get_overpayment(), 1E-1);
  ASSERT_NEAR(120833.33, model_calc.get_debt(), 1E-1);
  EXPECT_EQ(0, err);
}

TEST(Calculator, credit_3) {
  double credit = 1000000;
  double deadline = 1;
  double percent = 20;
  int type_credit = 1;
  int err =
      model_calc.credit_calculator(credit, deadline, percent, type_credit);
  ASSERT_NEAR(1016666.67, model_calc.get_payment_month(), 1E-1);
  ASSERT_NEAR(16666.67, model_calc.get_overpayment(), 1E-1);
  ASSERT_NEAR(1016666.67, model_calc.get_debt(), 1E-1);
  EXPECT_EQ(0, err);
}

TEST(Calculator, credit_4) {
  double credit = 1000000;
  double deadline = 1;
  double percent = 20;
  int type_credit = 2;
  int err =
      model_calc.credit_calculator(credit, deadline, percent, type_credit);
  ASSERT_NEAR(1016666.67, model_calc.get_min(), 1E-1);
  ASSERT_NEAR(1016666.67, model_calc.get_max(), 1E-1);
  ASSERT_NEAR(16666.67, model_calc.get_overpayment(), 1E-1);
  ASSERT_NEAR(1016666.67, model_calc.get_debt(), 1E-1);
  EXPECT_EQ(0, err);
}

TEST(Calculator, credit_5) {
  double credit = 1000000;
  double deadline = 600;
  double percent = 20;
  int type_credit = 2;
  int err =
      model_calc.credit_calculator(credit, deadline, percent, type_credit);
  ASSERT_NEAR(1694.44, model_calc.get_min(), 1E-1);
  ASSERT_NEAR(18333.33, model_calc.get_max(), 1E-1);
  ASSERT_NEAR(5008333.33, model_calc.get_overpayment(), 1E-1);
  ASSERT_NEAR(6008333.33, model_calc.get_debt(), 1E-1);
  EXPECT_EQ(0, err);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
