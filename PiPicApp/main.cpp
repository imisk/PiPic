#include "mainWindow.h"

#include <stdio.h>
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  std::cout << "PiPic starting..." << std::endl;

  return a.exec();

}
