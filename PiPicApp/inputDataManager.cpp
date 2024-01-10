#include <QDebug>
#include <QString>
#include <fstream>
#include <inputDataManager.h>
#include <iostream>
#include <logger.h>
#include <sstream>
#include <string>
#include <vector>

inputDataManager::inputDataManager()
{
    
}

void inputDataManager::loadPiFromDisk1Million(size_t maxDigitsToLoad, std::string &retNumber)
{
    std::string filePath = "pi_dec_1m.txt";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        Log() << "Unable to open file " << QString(filePath.c_str());
        return;
    }

    retNumber = "";
    file >> retNumber;

    file.close();

    if (maxDigitsToLoad < retNumber.length()) {
        retNumber = retNumber.substr(0, maxDigitsToLoad);
    }
}

std::vector<unsigned long int> inputDataManager::loadKnownCalculation(std::string &filePath)
{
    std::vector<unsigned long int> integers;
    std::ifstream file(filePath);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;

            while (std::getline(ss, value, ',')) {
                try {
                    integers.push_back(std::stoul(value));
                } catch (...) {
                }
            }
        }
        file.close();
    } else {
        Log() << "Unable to open file: " << QString(filePath.c_str());
        return integers;
    }

    Log() << "vec size = " << integers.size();

    for (int i = 0; i < 10; i++) {
        Log() << integers[i];
    }

    return integers;
}
