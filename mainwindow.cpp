#include "mainwindow.h"
#include <iostream>
#include "pipiccommon.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_btn_Test_clicked() {
  try {
    mainCore.benchmark_test();
  } catch (PiPicError& err) {
    std::cout << "PiPicError : " << static_cast<int>(err) << '\n';
  } catch (std::exception& ex) {
    std::cout << "Exception : " << ex.what() << '\n';
  } catch (...) {
    std::cout << "General exception \n";
  }
}
