#include "datamanager.h"
#include <fstream>
#include <vector>
#include "bhimutils.h"
#include "pipiccommon.h"

datamanager::datamanager() {}

void datamanager::Write_Value(std::string& fileName, BhimInteger val) {
  std::vector<uint8_t> digitVals;

  std::string fullPath = fileName;

  val.GetDigits(digitVals);

  auto saveFile =
      std::fstream(fullPath, std::ios::binary | std::ios::out | std::ios::ate);

  if (saveFile.good()) {
    uint32_t version = 0;
    dataWrite(saveFile, version);

    size_t digitCount = digitVals.size();
    dataWrite(saveFile, digitCount);

    for (auto& val : digitVals) {
      dataWrite(saveFile, val);
    }

  } else {
    throw PiPicException(PiPicError::CannotCreateFile);
  }

  saveFile.close();
}

void datamanager::Read_Value(string& fileName, BhimInteger& returnVal) {
  std::string fullPath = fileName;
  auto readFile =
      std::fstream(fullPath, std::ios::binary | std::ios::out | std::ios::in);

  if (readFile.good()) {
    uint32_t version = 0;
    dataRead(readFile, version);

    size_t digitCount = 0;
    dataRead(readFile, digitCount);

    std::vector<uint8_t> digitVals;

    for (size_t i = 0; i < digitCount; i++) {
      uint8_t dig = 0;
      dataRead(readFile, dig);

      digitVals.push_back(dig);
    }

    returnVal = to_BhimInteger(digitVals);

  } else {
    throw PiPicException(PiPicError::CannotLoadFile);
  }

  readFile.close();
}

template <typename T>
void datamanager::dataWrite(fstream& fs, T& val) {
  fs.write(reinterpret_cast<char*>(&val), sizeof(val));
}

template <typename T>
void datamanager::dataRead(fstream& fr, T& val) {
  fr.read(reinterpret_cast<char*>(&val), sizeof(val));
}
