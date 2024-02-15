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

    return integers;
}

double inputDataManager::getInformationRatioMultiplier(int base)
{
    /*This function looks up the values from informationRatioTable and returns and
     * interpolated value for the given base.
     * 
     * Reduce the value by linearityMultiplier because table uses linear interpolation,
     * while the real curve is logarithmic in nature, so just make sure you stay below it.
    */
    double linearityMultiplier = 0.97;

    if (base < informationRatioTable[0].base
        || base > informationRatioTable[informationRatioTable.size() - 1].base) {
        throw PiPicException(PiPicError::BaseOutOfRange);
    }

    for (size_t i = 0; i < informationRatioTable.size(); i++) {
        auto &itm = informationRatioTable[i];

        if (itm.base == base) {
            return itm.multiplier * linearityMultiplier;
        }

        if (itm.base > base) {
            //perform interpolation
            auto &prev = informationRatioTable[i - 1];
            double b = static_cast<double>(base);

            double unitsFromPrev = b - prev.base;

            double deltaPerUnit = (itm.multiplier - prev.multiplier) / (itm.base - prev.base);

            double totalDelta = unitsFromPrev * deltaPerUnit;

            double ret = prev.multiplier + totalDelta;

            ret *= linearityMultiplier;

            return ret;
        }
    }

    return 0.0;
}

int inputDataManager::getRequiredPiDecimalDigits(int targetBase, int targetDigits)
{
    double mul = getInformationRatioMultiplier(targetBase);

    double rd = static_cast<double>(targetDigits) / mul;

    return static_cast<int>(rd);
}

void inputDataManager::initInformationRatioTable()
{
    //These values have been derived empyrically using benchmark::accuracyTrialInputLength
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

void inputDataManager::initPrecisionRatioTable()
{
    //calculated using benchmark::accuracyTrialPrecMultiple
    precisionRatioTable.push_back({11, 3.45742});
    precisionRatioTable.push_back({16, 3.99787});
    precisionRatioTable.push_back({20, 4.31965});
    precisionRatioTable.push_back({30, 4.90356});
    precisionRatioTable.push_back({41, 5.35427});
    precisionRatioTable.push_back({60, 5.90319});
    precisionRatioTable.push_back({90, 6.48789});
    precisionRatioTable.push_back({150, 7.22369});
    precisionRatioTable.push_back({211, 7.71605});
    precisionRatioTable.push_back({300, 8.22368});
    precisionRatioTable.push_back({400, 8.63807});
    precisionRatioTable.push_back({567, 9.14077});
    precisionRatioTable.push_back({700, 9.44584});
    precisionRatioTable.push_back({900, 9.80713});
    precisionRatioTable.push_back({1200, 10.2215});
    precisionRatioTable.push_back({1511, 10.5522});
    precisionRatioTable.push_back({2000, 10.9609});
    precisionRatioTable.push_back({4000, 11.957});
    precisionRatioTable.push_back({8000, 12.959});
    precisionRatioTable.push_back({10001, 13.2802});
    precisionRatioTable.push_back({14000, 13.7678});
    precisionRatioTable.push_back({18000, 14.1243});
    precisionRatioTable.push_back({21755, 14.4023});
    precisionRatioTable.push_back({26000, 14.6556});
    precisionRatioTable.push_back({31291, 14.9254});
    precisionRatioTable.push_back({40000, 15.2749});
    precisionRatioTable.push_back({50000, 15.6006});
    precisionRatioTable.push_back({80000, 16.2778});
    precisionRatioTable.push_back({110000, 16.7317});
    precisionRatioTable.push_back({150000, 17.1821});
    precisionRatioTable.push_back({300000, 18.1818});
    precisionRatioTable.push_back({450000, 18.7617});
}
