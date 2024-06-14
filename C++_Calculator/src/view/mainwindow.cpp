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

// добавим защиту от двойной операции
void MainWindow::button_input() {
  QPushButton *button = (QPushButton *)sender();
  if (ch == "-" && button->text() == "-") {
  } else if (ch == "+" && button->text() == "+") {
  } else if (ch == "+" && button->text() == "-") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
  } else if (ch == "-" && button->text() == "+") {
    on_pushButton_AC_2_clicked();
    ui->lineEdit->setText(ui->lineEdit->text() + "+");
  } else if (ch == "/" && button->text() == "/") {
  } else if (ch == "*" && button->text() == "*") {
  } else {
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
  }
  ch = button->text();
}

// добавим автоматом скобку для триг функций
void MainWindow::button_input_s() {
  QPushButton *button = (QPushButton *)sender();
  ui->lineEdit->setText(ui->lineEdit->text() + button->text() + "(");
}

// отчистить результат полностью
void MainWindow::on_pushButton_AC_clicked() {
  ui->lineEdit->setText("");
  ui->lineEdit_5->setText("");
}

// стереть последний ввод
void MainWindow::on_pushButton_AC_2_clicked() {
  QString screen_result = ui->lineEdit->text();
  screen_result.chop(1);
  ui->lineEdit->setText(screen_result);
}

// вывести результат калькулятора
void MainWindow::on_pushButton_eq_clicked() {
  std::string str = ui->lineEdit->text().toStdString();
  double x_value = ui->lineEdit_x->text().toDouble();

  if (controller_.result_calculator(str, x_value) == 0) {
    ui->lineEdit_5->setText(
        QString::number(controller_.get_result_calculator(), 'g', 8));
  } else {
    ui->lineEdit_5->setText("error");
  }
}

// выводим график
void MainWindow::on_pushButton_graph_clicked() {
  int err = 0;
  double xBegin, xEnd, yBegin, yEnd;  // интервал
  double h;     // шаг между 2умя точками
  double X, Y;  // временные переменные для вектора
  QVector<double> x, y;  // храним координаты точек

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
    err = controller_.result_calculator(ui->lineEdit->text().toStdString(), X);
    Y = controller_.get_result_calculator();
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

// вывести результат кредит калькулятора
void MainWindow::on_pushButton_credit_clicked() {
  int err = 0;
  double credit = 0;
  double deadline = 0;
  double percent = 0;
  int type_credit = 0;
  if (ui->radioButton->isChecked()) {
    type_credit = 1;
  } else if (ui->radioButton_2->isChecked()) {
    type_credit = 2;
  } else {
    err = 1;
  }
  if (err == 0) {
    credit = ui->lineEdit_credit->text().toDouble();
    deadline = ui->lineEdit_deadline->text().toDouble();
    percent = ui->lineEdit_percent->text().toDouble();
    if (credit == 0 || deadline == 0 || percent == 0) {
      err = 1;
    }
  }
  if (err == 0) {
    err = controller_.result_credit_calculator(credit, deadline, percent,
                                               type_credit);

    if (type_credit == 1) {
      ui->lineEdit_payment->setText(
          QString::number(controller_.get_result_payment_month(), 'g', 8));
      ui->lineEdit_payment_2->setText(
          QString::number(controller_.get_result_payment_month(), 'g', 8));
      ui->lineEdit_over->setText(
          QString::number(controller_.get_result_overpayment(), 'g', 8));
      ui->lineEdit_debt->setText(
          QString::number(controller_.get_result_debt(), 'g', 8));
    } else if (type_credit == 2) {
      ui->lineEdit_payment->setText(
          QString::number(controller_.get_result_min(), 'g', 8));
      ui->lineEdit_payment_2->setText(
          QString::number(controller_.get_result_max(), 'g', 8));
      ui->lineEdit_over->setText(
          QString::number(controller_.get_result_overpayment(), 'g', 8));
      ui->lineEdit_debt->setText(
          QString::number(controller_.get_result_debt(), 'g', 8));
    }
  }
  if (err != 0) {
    ui->label_out->setText("err");
  } else {
    ui->label_out->setText("ok");
  }
}

// отчистить вывод кредит калькулятора
void MainWindow::on_pushButton_credit_2_clicked() {
  ui->lineEdit_payment->setText("");
  ui->lineEdit_payment_2->setText("");
  ui->lineEdit_over->setText("");
  ui->lineEdit_debt->setText("");
  ui->lineEdit_credit->setText("");
  ui->lineEdit_percent->setText("");
  ui->lineEdit_deadline->setText("");
}
