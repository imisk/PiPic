#include "bhimUtils.h"
#include <sstream>
#include <vector>

BhimInteger to_BhimInteger(vector<uint8_t> vec) {
    std::ostringstream convertstr;

    for (auto& d : vec) {
        std::string str = std::to_string(d);
        for (auto& c : str) {
            convertstr << c;
        }
    }

    std::string str2 = convertstr.str();
    BhimInteger N3(str2);
    return N3;
}
