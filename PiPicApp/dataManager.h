#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "bhimInteger.h"

/*
 * Writes and reads objects to/from disk.
 */
class datamanager {
 public:
  datamanager();

  void Write_Value(std::string& fileName, BhimInteger val);

  void Read_Value(std::string& fileName, BhimInteger& returnVal);

 private:
  template <typename T>
  void dataWrite(std::fstream& fs, T& val);

  template <typename T>
  void dataRead(std::fstream& fr, T& val);
};

#endif  // DATAMANAGER_H
