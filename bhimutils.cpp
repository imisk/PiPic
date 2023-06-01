#include "bhimutils.h"

BhimInteger to_BhimInteger(vector<uint8_t> vec) {
  ostringstream convertstr;

  char cv[1];

  constexpr size_t kDecimal = 10;
  for (auto& d : vec) {
    _itoa(d, &cv[0], kDecimal);
    convertstr << cv[0];
  }
  std::string str2 = convertstr.str();

  BhimInteger N3(str2);
  return N3;
}
