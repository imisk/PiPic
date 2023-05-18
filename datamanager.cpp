#include "datamanager.h"
#include <fstream>
#include <vector>

datamanager::datamanager() {}

void datamanager::SaveToFile_Value(std::string& fileName, BhimInteger val) {
  std::vector<uint8_t> digitVals;

  val.GetDigits(digitVals);

  auto saveFile =
      std::fstream(fileName, std::ios::binary | std::ios::out | std::ios::ate);

  if (saveFile.good()) {
    uint32_t version = 0;
    dataWrite(saveFile, version);

    size_t digitCount = digitVals.size();
    dataWrite(saveFile, digitCount);

    for (auto& val : digitVals) {
      dataWrite(saveFile, val);
    }

  } else {
    // todo throw error
  }

  saveFile.close();
}

template <typename T>
void datamanager::dataWrite(fstream& fs, T& val) {
  fs.write(reinterpret_cast<char*>(&val), sizeof(val));
}
