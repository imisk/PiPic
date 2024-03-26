#include "dataManager.h"
#include "logger.h"
#include <fstream>
#include <vector>

dataManager::dataManager() {}

void dataManager::writeDigitsToFile(QString &filename, std::vector<unsigned long> digits)
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

void dataManager::readDigitsFromFile(QString &fileName, std::vector<unsigned long> &retDigits)
{
    std::ifstream file;
    file.open(fileName.toStdString(), std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        Log() << "Error: readDigitsFromFile - could not open the file.";
    }

    size_t count;

    dataRead(file, count);

    for (size_t i = 0; i < count; i++) {
        unsigned long decimal;
        dataRead(file, decimal);
        retDigits.push_back(decimal);
    }

    file.close();
}

template<typename T>
void dataManager::dataWrite(std::ofstream &fs, T &val)
{
    fs.write(reinterpret_cast<char *>(&val), sizeof(val));
}

template<typename T>
void dataManager::dataRead(std::ifstream &fr, T &val)
{
    fr.read(reinterpret_cast<char *>(&val), sizeof(val));
}
