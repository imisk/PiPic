#include "utility.h"
#include <iostream>
#include "logger.h"

char decimalToHex(int decimal) {
  if (decimal >= 0 && decimal <= 9) {
    return static_cast<char>(decimal + '0');
  } else if (decimal >= 10 && decimal <= 15) {
    return static_cast<char>(decimal - 10 + 'A');
  } else {
    Log() << "decimalToHex - invalid argument \n";
    return '!';
  }
}

void reverseString(std::string& str) {
  size_t start = 0;
  size_t end = str.length() - 1;
  while (start < end) {
    std::swap(str[start], str[end]);
    start++;
    end--;
  }
}
