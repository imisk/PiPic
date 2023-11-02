#ifndef ERROR_MESSAGE_BOX_UTIL_H
#define ERROR_MESSAGE_BOX_UTIL_H

#include <QString>

class PiPicException;

void HandleErrorMessage(const PiPicException& err);

void ShowMessageBox(QString message);

void ShowMessageBox(const char* message);

void HandleGeneralError();

#endif  // ERROR_MESSAGE_BOX_UTIL_H
