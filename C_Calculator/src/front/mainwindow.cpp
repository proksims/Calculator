#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(button_input_s()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(button_input()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(button_input()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::button_input() {
  QPushButton *button = (QPushButton *)sender();

  if (ch == "-" && button->text() == "-") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
  } else if (ch == "+" && button->text() == "+") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "+");
  } else if (ch == "+" && button->text() == "-") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
  } else if (ch == "-" && button->text() == "+") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "+");
  } else if (ch == "*" && button->text() == "-") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "*(-");
  } else if (ch == "*" && button->text() == "+") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "*(+");
  } else if (ch == "/" && button->text() == "-") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "/(-");
  } else if (ch == "/" && button->text() == "+") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "/(+");
  } else if (ch == "/" && button->text() == "/") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "/");
  } else if (ch == "*" && button->text() == "*") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "*");
  } else if ((ch == "1" || ch == "2" || ch == "3" || ch == "4" || ch == "5" ||
              ch == "6" || ch == "7" || ch == "8" || ch == "9" || ch == "0") &&
             button->text() == "x") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*x");
  } else if (ch == "x" && button->text() == "(") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*(");
  } else if (ch == ")" && button->text() == "x") {
    ui->lineEdit->setText(ui->lineEdit->text() + "*x");
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  }
  ch = button->text();
}

void MainWindow::button_input_s() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text() + "(");
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->lineEdit->setText("");
  ui->lineEdit_5->setText("");
}

void MainWindow::on_pushButton_eq_clicked() {
  QString str_result;
  x_value = ui->lineEdit_x->text().toDouble();
  double result;
  int err;

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
  err = calculator((char *)ui->lineEdit->text().toStdString().c_str(), x_value,
                   &result);
  if (err == 0) {
    str_result = QString::number(result, 'g', 8);
    ui->lineEdit_5->setText(str_result);
  } else if (err == 1) {
    ui->lineEdit_5->setText("err");
  } else if (err == 2) {
    ui->lineEdit_5->setText("err start");
  } else if (err == 3) {
    ui->lineEdit_5->setText("err end");
  } else if (err == 4) {
    ui->lineEdit_5->setText("err");
  } else if (err == 5) {
    ui->lineEdit_5->setText("err div 0");
  } else if (err == 6) {
    ui->lineEdit_5->setText("err with ( )");
  } else if (err == 7) {
    ui->lineEdit_5->setText("err size");
  } else if (err == 8) {
    ui->lineEdit_5->setText("err func");
  } else if (err == 9) {
    ui->lineEdit_5->setText("err mod");
  } else if (err == 10) {
    ui->lineEdit_5->setText("err operation");
  } else if (err == 11) {
    ui->lineEdit_5->setText("negative sqrt");
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  int err = 0;
  ui->widget->clearGraphs();

  xBegin = ui->lineEdit_xmin->text().toDouble();
  xEnd = ui->lineEdit_xmax->text().toDouble();
  yBegin = ui->lineEdit_ymax->text().toDouble();
  yEnd = ui->lineEdit_ymin->text().toDouble();

  if (xEnd - xBegin <= 1) {
    h = 0.001;
  } else if (xEnd - xBegin >= 1000) {
    h = 1;
  } else {
    h = 0.01;
  }

  if (xBegin < -1000000.0) xBegin = -1000000.0;
  if (xEnd > 1000000.0) xEnd = 1000000.0;
  if (yBegin < -1000000.0) yBegin = -1000000.0;
  if (yEnd > 1000000.0) yEnd = 1000000.0;

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  for (X = xBegin; X <= xEnd; X += h) {
    err = calculator((char *)ui->lineEdit->text().toStdString().c_str(), X, &Y);
    x.push_back(X);
    if (err != 0) {
      y.push_back(NAN);
    } else {
      y.push_back(Y);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  x.clear();
  y.clear();
}

// typedef struct credit_calculator {
//         // вход
//         double credit;
//         double deadline;
//         double percent;
//         int type_credit;
//         // выход
//         double payment_month;
//         double payment_month_min;
//         double payment_month_max;
//         double overpayment;
//         double debt;
// } my_credit_calculator;

void MainWindow::on_pushButton_credit_clicked() {
  int err = 0;
  data->credit = 0;
  data->deadline = 0;
  data->percent = 0;

  if (ui->radioButton->isChecked()) {
    data->type_credit = 1;
  } else if (ui->radioButton_2->isChecked()) {
    data->type_credit = 2;
  } else {
    err = 1;
  }
  if (err == 0) {
    data->credit = ui->lineEdit_credit->text().toDouble();
    data->deadline = ui->lineEdit_deadline->text().toDouble();
    data->percent = ui->lineEdit_percent->text().toDouble();
    if (data->credit == 0 || data->deadline == 0 || data->percent == 0) {
      err = 1;
    }
  }

  if (err == 0) {
    err = f_credit_calculator(data);

    if (data->type_credit == 1) {
      ui->lineEdit_payment->setText(
          QString::number(data->payment_month, 'g', 8));
      ui->lineEdit_payment_2->setText(
          QString::number(data->payment_month, 'g', 8));
      ui->lineEdit_over->setText(QString::number(data->overpayment, 'g', 8));
      ui->lineEdit_debt->setText(QString::number(data->debt, 'g', 8));
    } else if (data->type_credit == 2) {
      ui->lineEdit_payment->setText(
          QString::number(data->payment_month_min, 'g', 8));
      ui->lineEdit_payment_2->setText(
          QString::number(data->payment_month_max, 'g', 8));
      ui->lineEdit_over->setText(QString::number(data->overpayment, 'g', 8));
      ui->lineEdit_debt->setText(QString::number(data->debt, 'g', 8));
    }
  }
  if (err != 0) {
    ui->label_out->setText("err");
  } else {
    ui->label_out->setText("ok");
  }
}

void MainWindow::on_pushButton_credit_2_clicked() {
  ui->lineEdit_payment->setText("");
  ui->lineEdit_payment_2->setText("");
  ui->lineEdit_over->setText("");
  ui->lineEdit_debt->setText("");
  ui->lineEdit_credit->setText("");
  ui->lineEdit_percent->setText("");
  ui->lineEdit_deadline->setText("");
}

void MainWindow::on_pushButton_AC_2_clicked() {
  QString screen_result = ui->lineEdit->text();
  screen_result.chop(1);
  ui->lineEdit->setText(screen_result);
}
