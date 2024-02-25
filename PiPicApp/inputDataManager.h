#ifndef INPUTDATAMANAGER_H
#define INPUTDATAMANAGER_H

#include <QString>
#include <piPicCommon.h>
#include <vector>

class inputDataManager
{
public:
    inputDataManager();

    //Loads Pi value from large text file
    void loadPiFromDisk1Million(size_t maxDigitsToLoad, std::string &retNumber);

    //Load digits (any base) from text file. File text format "123,456,223"
    std::vector<unsigned long int> loadCommaSeparatedValues(std::string &filePath);

    //If you have N digits in base 10 representation, you can calculate N*multiplier digits in base representation
    double getInformationRatioMultiplier(int base);

    int getRequiredPiDecimalDigits(int targetBase, int targetDigitCount);

    unsigned long int getRequiredPrecision(int targetBase, int targetDigitCount);

private:
    double getInterpolatedValueFromTable(int base, std::vector<baseTableValue> &table);
    std::vector<baseTableValue> informationRatioTable;

    std::vector<baseTableValue> precisionRatioTable;

    void initInformationRatioTable();

    void initPrecisionRatioTable();
};

#endif // INPUTDATAMANAGER_H
