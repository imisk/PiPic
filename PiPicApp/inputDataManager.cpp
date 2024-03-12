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

void inputDataManager::loadPiFromDisk1Billion(size_t maxDigitsToLoad, std::string &retNumber)
{
    if (maxDigitsToLoad > 1000000000) {
        Log() << "Error: cannot load more than 1 billion decimals of Pi.";
        return;
    }

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

void inputDataManager::loadPiFromDisk1Million(size_t maxDigitsToLoad, std::string &retNumber)
{
    if (maxDigitsToLoad > 1000000) {
        Log() << "Error: if you want to load more than 1 million digits, use a different function.";
        return;
    }

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
    //only add linearityMultiplier

    /*This function looks up the values from informationRatioTable and returns and
     * interpolated value for the given base.
     * 
     * Reduce the value by linearityMultiplier because table uses linear interpolation,
     * while the real curve is logarithmic in nature, so just make sure you stay below it.
    */
    double linearityMultiplier = 0.97;

    double ret = getInterpolatedValueFromTable(base, informationRatioTable);

    return ret * linearityMultiplier;
}

int inputDataManager::getRequiredPiDecimalDigits(int targetBase, int targetDigits)
{
    double mul = getInformationRatioMultiplier(targetBase);

    double rd = static_cast<double>(targetDigits) / mul;

    return static_cast<int>(rd);
}

unsigned long int inputDataManager::getRequiredPrecision(int targetBase, int targetDigitCount)
{
    //required precision = digits to calculate * ratio

    //if you reduce safetyMultiplier, maybe minor speedup and memory saving. 0.9 would mean the last 10% digits are wrong.
    double safetyMultiplier = 1.05;

    double ratio = getInterpolatedValueFromTable(targetBase, precisionRatioTable);

    double precisionRequired = static_cast<double>(targetDigitCount) * ratio;

    precisionRequired *= safetyMultiplier;

    return static_cast<unsigned long int>(precisionRequired);
}

double inputDataManager::getInterpolatedValueFromTable(int base, std::vector<baseTableValue> &table)
{
    if (base < table[0].base || base > table[table.size() - 1].base) {
        throw PiPicException(PiPicError::BaseOutOfRange);
    }

    for (size_t i = 0; i < table.size(); i++) {
        auto &itm = table[i];

        if (itm.base == base) {
            return itm.value;
        }

        if (itm.base > base) {
            //perform interpolation
            auto &prev = table[i - 1];
            double b = static_cast<double>(base);

            double unitsFromPrev = b - prev.base;

            double deltaPerUnit = (itm.value - prev.value) / (itm.base - prev.base);

            double totalDelta = unitsFromPrev * deltaPerUnit;

            double ret = prev.value + totalDelta;

            return ret;
        }
    }

    return 0.0;
}

void inputDataManager::initInformationRatioTable()
{
    /*For a given base, if you are using Pi in base 10 as input, you need to calculate
     * how many digits your input length can produce. For larger bases, you can produce
     * fewer digits before the accuracy decreases, because each digit contains more
     * information. The multiplier tells you how many accurate digits you can expect
     * based on the number of base10 pi digits you have as input.
    */

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
}

void inputDataManager::initPrecisionRatioTable()
{
    //The ratio between the required precision bits and target base

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
