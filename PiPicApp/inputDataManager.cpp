#include <QDebug>
#include <QString>
#include <fstream>
#include <inputDataManager.h>
#include <logger.h>
#include <string>

inputDataManager::inputDataManager()
{
    
}

void inputDataManager::loadPiFromDisk1Million(size_t maxDigitsToLoad, QString &retNumber)
{
    std::string filePath = "pi_dec_1m.txt";

    std::ifstream file(filePath);
    if (!file.is_open()) {
        Log() << "Unable to open file " << QString(filePath.c_str());
        return;
    }

    std::string number;
    file >> number;

    file.close();

    if (maxDigitsToLoad < number.length()) {
        number = number.substr(0, maxDigitsToLoad);
    }

    retNumber = QString(number.c_str());

    Log() << "retNumber = " << retNumber;
}
