#ifndef PIPICCOMMON_H
#define PIPICCOMMON_H

#include <iostream>

enum class PiPicError { OK = 0, CannotCreateFile = 1, CannotLoadFile = 2, BadFileName = 3 };

struct baseDigitInformationRatioItem
{
    /*For a given base, if you are using Pi in base 10 as input, you need to calculate
     * how many digits your input length can produce. For larger bases, you can produce
     * fewer digits before the accuracy decreases, because each digit contains more
     * information. The multiplier tells you how many accurate digits you can expect
     * based on the number of base10 pi digits you have as input.
    */
    int base;
    double multiplier;

    bool operator<(baseDigitInformationRatioItem& other) { return base < other.base; }
};

class PiPicException : public std::exception {
 public:
  explicit PiPicException(PiPicError err) : pipicError(err) {
      generateMessage();
  }

  PiPicException(PiPicError err, const std::string& additionalMessage)
      : pipicError(err), AdditionalMessage(additionalMessage) {
      generateMessage();
  }

  PiPicException(PiPicError err, const char* msg)
      : pipicError(err), AdditionalMessage(msg) {
      generateMessage();
  }

  char const* what() const noexcept override {
      return FullMessage.c_str();
  }

  PiPicError GetError() { return pipicError; }

 private:

  void generateMessage() {
    std::string msg1;

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

    FullMessage = msg1 + "\n" + AdditionalMessage;
  }
  PiPicError pipicError;
  std::string AdditionalMessage;
  std::string FullMessage;
};

#endif  // PIPICCOMMON_H
