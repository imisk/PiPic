#include "mainwindow.h"
#include <iostream>
#include "error_message_box_util.h"
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

  qDebug() << "Test clicked";

  try {
    mainCore.benchmark_test();
  } catch (std::bad_alloc err1) {
    // PiPicException err(PiPicError::BadFileName);
    // HandleErrorMessage(err);
    std::cout << "eerrrooorrr \n";
  }  // catch (...) {
  //    HandleGeneralError();
  //  }

  std::cout << "Test button finished \n";
}
