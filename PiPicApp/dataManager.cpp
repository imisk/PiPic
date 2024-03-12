#include "dataManager.h"
#include "logger.h"
#include <fstream>
#include <vector>

datamanager::datamanager() {}

void datamanager::writeDigitsToFile(QString &filename, std::vector<unsigned long> digits)
{
    std::ofstream file;

    // Open the file in write mode
    file.open(filename.toStdString(), std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        Log() << "Error: Could not open the file.";
    }

    size_t ds = digits.size();

    dataWrite(file, ds);

    for (unsigned long digit : digits) {
        dataWrite(file, digit);
    }

    file.close();

    Log() << "writeDigitsToFile - Finished writing.";
}

template<typename T>
void datamanager::dataWrite(std::ofstream &fs, T &val)
{
    fs.write(reinterpret_cast<char *>(&val), sizeof(val));
}

template<typename T>
void datamanager::dataRead(std::fstream &fr, T &val)
{
    fr.read(reinterpret_cast<char *>(&val), sizeof(val));
}
