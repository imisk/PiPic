#include "mainWindow.h"
#include "errorMessageBoxUtil.h"
#include "logStream.h"
#include "logger.h"
#include "piPicCommon.h"
#include "ui_mainWindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainCore(this)
{
  ui->setupUi(this);

    mwp = this;

    connect(this, &MainWindow::logMessageReceived, this, &MainWindow::appendLogMessage);
}

MainWindow::~MainWindow() {
  delete ui;
}



void MainWindow::on_btn_Test_clicked() {


  Log() << "Testing logger! Here is a value of five: " << 5;

  try {
    //mainCore.benchmark_test();

      mainCore.trial();



  } catch (std::bad_alloc& err1) {
    // PiPicException err(PiPicError::BadFileName);
    // HandleErrorMessage(err);
    Log() << "eerrrooorrr \n";

  }
  catch(PiPicException& exc)
  {
    HandleErrorMessage(exc);
  }
  catch (...) {
      HandleGeneralError();
    }

    Log() << "Test button finished \n";
}

void MainWindow::appendLogMessage(const QString &message)
{
  ui->pte_Log->appendPlainText(message);
}

void MainWindow::updateDigitProgress(int curDigit)
{
  ui->lbl_CurDigit->setText(QString::number(curDigit));
}
