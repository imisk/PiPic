#include "utility.h"
#include <iostream>

char decimalToHex(int decimal) {
  if (decimal >= 0 && decimal <= 9) {
    return static_cast<char>(decimal + '0');
  } else if (decimal >= 10 && decimal <= 15) {
    return static_cast<char>(decimal - 10 + 'A');
  } else {
    std::cout << "decimalToHex - invalid argument \n";
    return '!';
  }
}

void reverseString(std::string& str) {
  int start = 0;
  int end = str.length() - 1;
  while (start < end) {
    std::swap(str[start], str[end]);
    start++;
    end--;
  }
}
