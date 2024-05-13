#include "benchmark.h"
#include <iostream>

#include <QApplication>
#include <calculator.h>
#include <chrono>
#include <dataManager.h>
#include <inputDataManager.h>
#include <logger.h>
#include <paletteManager.h>

benchmark::benchmark(inputDataManager *nInputDataManager, calculator *nCalc)
    : inputDataMngr(nInputDataManager)
    , calc(nCalc)
{}

void benchmark::accuracyTrialInputLength()
{
    std::string filePathKnownCalc = "10k/450000.txt"; //variable

    std::vector<unsigned long int> knownDigits = inputDataMngr->loadCommaSeparatedValues(
        filePathKnownCalc);

    //How long the source Pi string will be
    size_t currentInputLength = 1000;

    for (currentInputLength = 1000; currentInputLength < 20000; currentInputLength += 2000) {
        std::string pi;

        inputDataMngr->loadPiFromDisk1Million(currentInputLength, pi);

        std::vector<unsigned long int> digits
            = calc->convertNumberToBase(pi, 450000, 10000, 10000000); //base is variable

        bool finished = false;

        size_t i = 1;
        while (!finished) {
            if (digits[i] != knownDigits[i]) {
                finished = true;
            }
            i++;

            if (i > digits.size() - 1 || i > knownDigits.size() - 1) {
                finished = true;
            }
        }

        Log() << "InputLen = " << currentInputLength << " _ match count = " << i;

        double ratio = static_cast<double>(i) / static_cast<double>(currentInputLength);

        Log() << "ratio = " << ratio;
        QApplication::processEvents();
    }
}

void benchmark::test()
{
    paletteManager pm;

    pm.createColourWheel_BlackAndWhiteNoRedRight();
}

void benchmark::accuracyTrialPrec()
{
    /*
     * Test results:
     * 
     * for base 111, if precision is 500000, the number of calculable digits is 73595. ratio == 6.79394
     * the ratio is about the same for precisions between 100k and 600k +/-0.001
     * 
     * for base 32555, ratio is 14.988
     * 
     * calculable digits is the number of digits that can be calculated for the target base, in target base.
     * 
     * formula:
     * calculable digits = precision / ratio
     * 
     * required precision = digits to calculate * ratio
     * 
     * */
    std::string filePathKnownCalc = "100k/32555.txt"; //variable

    int base = 32555;
    int digitsToCalculate = 100000;

    std::vector<unsigned long int> knownDigits = inputDataMngr->loadCommaSeparatedValues(
        filePathKnownCalc);

    int currentInputLength = inputDataMngr->getRequiredPiDecimalDigits(base, digitsToCalculate);

    Log() << "currentInputLength = " << currentInputLength;

    std::string pi;

    inputDataMngr->loadPiFromDisk1Million(currentInputLength, pi);

    for (unsigned long int precision = 100000; precision < 1000000; precision += 100000) {
        std::vector<unsigned long int> digits
            = calc->convertNumberToBase(pi, base, digitsToCalculate, precision); //base is variable

        bool finished = false;

        size_t i = 1;
        while (!finished) {
            if (digits[i] != knownDigits[i]) {
                finished = true;
            }
            i++;

            if (i > digits.size() - 1 || i > knownDigits.size() - 1) {
                finished = true;
            }
        }

        double ratio = static_cast<double>(precision) / static_cast<double>(i);

        Log() << "precision = " << precision << " _ match count = " << i << " _ ratio = " << ratio;
        QApplication::processEvents();
    }
}

void benchmark::accuracyTrialPrecMultiple()
{
    std::vector<std::string> filePaths;

    filePaths.push_back("10k/11.txt");
    filePaths.push_back("10k/16.txt");
    filePaths.push_back("10k/20.txt");
    filePaths.push_back("10k/30.txt");
    filePaths.push_back("10k/41.txt");
    filePaths.push_back("10k/60.txt");
    filePaths.push_back("10k/90.txt");
    filePaths.push_back("10k/150.txt");
    filePaths.push_back("10k/211.txt");
    filePaths.push_back("10k/300.txt");
    filePaths.push_back("10k/400.txt");
    filePaths.push_back("10k/567.txt");
    filePaths.push_back("10k/700.txt");
    filePaths.push_back("10k/900.txt");
    filePaths.push_back("10k/1200.txt");
    filePaths.push_back("10k/1511.txt");
    filePaths.push_back("10k/2000.txt");
    filePaths.push_back("10k/4000.txt");
    filePaths.push_back("10k/8000.txt");
    filePaths.push_back("10k/10001.txt");
    filePaths.push_back("10k/14000.txt");
    filePaths.push_back("10k/18000.txt");
    filePaths.push_back("10k/21755.txt");
    filePaths.push_back("10k/26000.txt");
    filePaths.push_back("10k/31291.txt");
    filePaths.push_back("10k/40000.txt");
    filePaths.push_back("10k/50000.txt");
    filePaths.push_back("10k/80000.txt");
    filePaths.push_back("10k/110000.txt");
    filePaths.push_back("10k/150000.txt");
    filePaths.push_back("10k/300000.txt");
    filePaths.push_back("10k/450000.txt");

    std::vector<int> baseVec{11,    16,    20,    30,    41,     60,     90,     150,
                             211,   300,   400,   567,   700,    900,    1200,   1511,
                             2000,  4000,  8000,  10001, 14000,  18000,  21755,  26000,
                             31291, 40000, 50000, 80000, 110000, 150000, 300000, 450000};

    int digitsToCalculate = 10000;

    int precision = 30000;

    for (size_t i = 0; i < baseVec.size(); i++) {
        int base = baseVec[i];
        std::string &filePathKnownCalc = filePaths[i];

        std::vector<unsigned long int> knownDigits = inputDataMngr->loadCommaSeparatedValues(
            filePathKnownCalc);

        int currentInputLength = inputDataMngr->getRequiredPiDecimalDigits(base, digitsToCalculate);

        std::string pi;

        inputDataMngr->loadPiFromDisk1Million(currentInputLength, pi);

        std::vector<unsigned long int> digits
            = calc->convertNumberToBase(pi, base, digitsToCalculate, precision); //base is variable

        bool finished = false;

        size_t k = 2;
        while (!finished) {
            if (digits[k] != knownDigits[k]) {
                finished = true;
            }
            k++;

            if (k > digits.size() - 1 || k > knownDigits.size() - 1) {
                finished = true;
            }
        }

        double ratio = static_cast<double>(precision) / static_cast<double>(k);

        Log() << "inpLen = " << currentInputLength << " _ precision = " << precision
              << " _ match count = " << k << " _ ratio = " << ratio << " _ base = " << base;
        QApplication::processEvents();
    }
}

void benchmark::saveLoadTrial()
{
    std::vector<unsigned long> vec = {233, 441, 2231, 4432421, 21342, 122313, 43422};

    dataManager dm;

    QString fn = "test123.dec";

    dm.writeDigitsToFile(fn, vec);

    std::vector<unsigned long> v2;

    dm.readDigitsFromFile(fn, v2);

    for (auto &d : v2) {
        Log() << d;
    }
}
