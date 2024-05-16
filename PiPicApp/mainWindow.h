#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core.h"
#include <string>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;


signals:
    void logMessageReceived(const QString& message);

public slots:
    void updateDigitProgress(int curDigit);
private slots:
    void on_btn_Test_clicked();
    void appendLogMessage(const QString& message);

private:
    Ui::MainWindow* ui;

    core mainCore;
};
#endif  // MAINWINDOW_H
