#include "benchmark.h"
#include <iostream>

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
    std::string filePathKnownCalc = "10k/41.txt";

    std::vector<unsigned long int> knownDigits = inputDataMngr->loadKnownCalculation(
        filePathKnownCalc);

    size_t currentInputLength = 1000;

    std::string pi;

    inputDataMngr->loadPiFromDisk1Million(currentInputLength, pi);

    std::vector<unsigned long int> digits = calc->convertNumberToBase(pi, 41, 100);

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

    Log() << "match count = " << i;
}

void benchmark::test() {}
