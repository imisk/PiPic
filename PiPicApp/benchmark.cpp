#include "benchmark.h"
#include <iostream>

#include <QApplication>
#include <calculator.h>
#include <chrono>
#include <inputDataManager.h>
#include <logger.h>

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

        std::vector<unsigned long int> digits = calc->convertNumberToBase(pi,
                                                                          450000,
                                                                          10000); //base is variable

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

void benchmark::test() {}
