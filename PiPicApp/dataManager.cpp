#include "dataManager.h"
#include <fstream>
#include <vector>

datamanager::datamanager() {}

template<typename T>
void datamanager::dataWrite(std::fstream &fs, T &val)
{
    fs.write(reinterpret_cast<char *>(&val), sizeof(val));
}

template<typename T>
void datamanager::dataRead(std::fstream &fr, T &val)
{
    fr.read(reinterpret_cast<char *>(&val), sizeof(val));
}
