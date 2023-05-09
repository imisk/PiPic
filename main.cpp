#include "mainwindow.h"

#include <Windows.h>
#include <stdio.h>
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[]) {
  /*
  detach from the current console window
  if launched from a console window, that will still run waiting for the
    new console (below) to close.
  it is useful to detach from Qt Creator's <Application output> panel.
*/
  FreeConsole();

  // create a separate new console window
  AllocConsole();

  // attach the new console to this application's process
  AttachConsole(GetCurrentProcessId());

  // reopen the std I/O streams to redirect I/O to the new console
  freopen("CON", "w", stdout);
  freopen("CON", "w", stderr);
  freopen("CON", "r", stdin);

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  std::cout << "PiPic starting..." << std::endl;

  return a.exec();
}
