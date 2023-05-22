#include "bhimutils.h"

BhimInteger to_BhimInteger(vector<uint8_t> vec) {
  ostringstream convertstr;
  cout << "bh start \n";
  char cv[1];

  constexpr size_t kDecimal = 10;
  for (auto& d : vec) {
    _itoa(d, &cv[0], kDecimal);
    convertstr << cv[0];
  }
  cout << "bh p2 \n";

  std::string str2 = convertstr.str();

  cout << "str2 = " << str2 << '\n';

  BhimInteger N3(str2);
  cout << "bh p3 \n";
  return N3;
}
