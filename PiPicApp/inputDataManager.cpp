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
    initInformationRatioTable();
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

std::vector<unsigned long int> inputDataManager::loadCommaSeparatedValues(std::string &filePath)
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

    for (int i = 0; i < 10; i++) {
        Log() << integers[i];
    }

    return integers;
}

double inputDataManager::getInformationRatioMultiplier(int base)
{
    /*
     * Reduce the value by linearityMultiplier because table uses linear interpolation,
     * while the real curve is logarithmic in nature.
    */
    double linearityMultiplier = 0.97;
}

void inputDataManager::initInformationRatioTable()
{
    //These values have been derived empyrically
    informationRatioTable.push_back({11, 0.959});
    informationRatioTable.push_back({16, 0.829});
    informationRatioTable.push_back({20, 0.767});
    informationRatioTable.push_back({30, 0.676});
    informationRatioTable.push_back({41, 0.619});
    informationRatioTable.push_back({60, 0.562});
    informationRatioTable.push_back({90, 0.511});
    informationRatioTable.push_back({150, 0.459});
    informationRatioTable.push_back({211, 0.43});
    informationRatioTable.push_back({300, 0.403});
    informationRatioTable.push_back({400, 0.384});
    informationRatioTable.push_back({567, 0.363});
    informationRatioTable.push_back({700, 0.351});
    informationRatioTable.push_back({900, 0.338});
    informationRatioTable.push_back({1200, 0.324});
    informationRatioTable.push_back({1511, 0.314});
    informationRatioTable.push_back({2000, 0.3028});
    informationRatioTable.push_back({4000, 0.277});
    informationRatioTable.push_back({8000, 0.256});
    informationRatioTable.push_back({10001, 0.25});
    informationRatioTable.push_back({14000, 0.241});
    informationRatioTable.push_back({18000, 0.235});
    informationRatioTable.push_back({21755, 0.23});
    informationRatioTable.push_back({26000, 0.226});
    informationRatioTable.push_back({31291, 0.222});
    informationRatioTable.push_back({40000, 0.217});
    informationRatioTable.push_back({50000, 0.2125});
    informationRatioTable.push_back({80000, 0.2039});
    informationRatioTable.push_back({110000, 0.198});
    informationRatioTable.push_back({150000, 0.193});
    informationRatioTable.push_back({300000, 0.1824});
    informationRatioTable.push_back({450000, 0.1767});

    std::sort(informationRatioTable.begin(), informationRatioTable.end());

    for (auto &r : informationRatioTable) {
        Log() << "base = " << r.base << " _ mul = " << r.multiplier;
    }
}
