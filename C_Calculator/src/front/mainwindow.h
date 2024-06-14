#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

// extern "C" {
// #include "./calculator.h"
// }

#ifdef __cplusplus
extern "C" {
#endif
#include "../model/calculator.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QString ch = "q";
  double x_value;
  double xBegin, xEnd, yBegin, yEnd;  // интервал
  double h;     // шаг между 2умя точками
  double X, Y;  // временные переменные для вектора

  QVector<double> x, y;  // храним координаты точек

  my_credit_calculator A;
  my_credit_calculator *data = &A;

 private slots:
  void button_input();
  void button_input_s();
  void on_pushButton_AC_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_credit_2_clicked();
  void on_pushButton_AC_2_clicked();
};

#endif  // MAINWINDOW_H
