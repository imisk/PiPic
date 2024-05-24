#include "dataManager.h"
#include "logger.h"
#include <fstream>
#include <vector>

dataManager::dataManager() {}

void dataManager::writeDigitsToFile(QString &filename, std::vector<unsigned long> digits, int base)
{
    std::ofstream file;

    // Open the file in write mode
    file.open(filename.toStdString(), std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        Log() << "Error: Could not open the file.";
        return;
    }

    unsigned char digitSize = writeHeader(file, base);

    size_t ds = digits.size();

    dataWrite(file, ds);

    for (unsigned long digit : digits) {
        if (digitSize == 0) {
            unsigned char val = static_cast<unsigned char>(digit);
            dataWrite(file, val);
        } else if (digitSize == 1) {
            unsigned short int val = static_cast<unsigned short int>(digit);
            dataWrite(file, val);
        } else if (digitSize == 2) {
            unsigned int val = static_cast<unsigned int>(digit);
            dataWrite(file, val);
        } else {
            dataWrite(file, digit);
        }
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
        return;
    }

    int base = -1;

    unsigned char digitSize = readHeader(file, base);

    if (digitSize == 250) {
        //todo : 250 should be constexpr value
        Log() << "Error : file header corrupted.";
        return;
    }

    size_t count;
    dataRead(file, count);

    for (size_t i = 0; i < count; i++) {
        if (digitSize == 0) {
            unsigned char val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned long>(val));
        } else if (digitSize == 1) {
            unsigned short int val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned short int>(val));
        } else if (digitSize == 2) {
            unsigned int val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned int>(val));
        } else {
            unsigned long decimal;
            dataRead(file, decimal);
            retDigits.push_back(decimal);
        }
    }

    file.close();
}

unsigned char dataManager::writeHeader(std::ofstream &fs, int base)
{
    uchar id = 0;

    if (base <= std::numeric_limits<unsigned char>::max()) {
        id = 0; //use bytes
    } else if (base <= std::numeric_limits<unsigned short int>::max()) {
        id = 1; //use shorts
    } else if (base <= std::numeric_limits<unsigned int>::max()) {
        id = 2; //use ints
    } else {
        id = 3; //use longs
    }

    uchar n = 18;
    dataWrite(fs, n);

    n = 11;
    dataWrite(fs, n);

    n = 21;
    dataWrite(fs, n);

    dataWrite(fs, id);

    dataWrite(fs, base);

    return id;
}

unsigned char dataManager::readHeader(std::ifstream &fr, int &retBase)
{
    uchar n1;
    dataRead(fr, n1);

    uchar n2;
    dataRead(fr, n2);

    uchar n3;
    dataRead(fr, n3);

    uchar id;
    dataRead(fr, id);

    if (n1 != 18 || n2 != 11 || n3 != 21) {
        return 250; //todo: add exception
    }

    dataRead(fr, retBase);

    return id;
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
