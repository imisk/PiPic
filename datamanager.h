#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "BhimInteger.h"

class datamanager {
 public:
  datamanager();

  void SaveToFile_Value(std::string& fileName, BhimInteger val);

 private:
  template <typename T>
  void dataWrite(std::fstream& fs, T& val);
};

#endif  // DATAMANAGER_H
