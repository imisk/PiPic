#ifndef PIPICCOMMON_H
#define PIPICCOMMON_H

#include <iostream>

enum class PiPicError {
  OK = 0,
  CannotCreateFile = 1,
  CannotLoadFile = 2,
  BadFileName = 3
};

static std::string exceptionTxt;

class PiPicException : public std::exception {
 public:
  explicit PiPicException(PiPicError& err) : pipicError(err) {}

  explicit PiPicException(PiPicError&& err) : pipicError(err) {}

  PiPicException(PiPicError& err, std::string& additionalMessage)
      : pipicError(err), AdditionalMessage(additionalMessage) {}

  PiPicException(PiPicError err, const char* msg)
      : pipicError(err), AdditionalMessage(msg) {}

  char const* what() const override {
    std::string msg1;

    std::cout << "exception __ what = " << static_cast<int>(pipicError)
              << std::endl;

    msg1 = "Unknown error";

    switch (pipicError) {
      case PiPicError::OK:
        msg1 = "No error";
        break;
      case PiPicError::CannotCreateFile:
        msg1 = "Could not create file \n";
        break;
      case PiPicError::CannotLoadFile:
        msg1 = "Could not load file \n";
        break;
      case PiPicError::BadFileName:
        msg1 = "Bad file name \n";
        break;
    }

    exceptionTxt = msg1 + "\n";
    exceptionTxt = exceptionTxt + AdditionalMessage;

    return exceptionTxt.c_str();
  }

  PiPicError GetError() { return pipicError; }

 private:
  PiPicError pipicError;
  std::string AdditionalMessage;
};

#endif  // PIPICCOMMON_H
