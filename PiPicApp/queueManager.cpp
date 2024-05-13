#include "queueManager.h"
#include "calculator.h"
#include "dataManager.h"
#include "inputDataManager.h"
#include "logger.h"
#include <chrono>
#include <imageManager.h>
#include <string>

queueManager::queueManager()
{
    
    
}

void queueManager::executeItem()
{
    auto start = std::chrono::high_resolution_clock::now();

    int base = 11;
    //size_t targetDigits = 8294400; //4x
    size_t targetDigits = 2073600;

    //size_t targetDigits = 2000;

    calculator calc;
    inputDataManager idm;
    dataManager dm;

    int requiredPiDecimals = idm.getRequiredPiDecimalDigits(base, targetDigits);

    std::string pi;

    idm.loadPiFromDisk1Billion(static_cast<size_t>(requiredPiDecimals), pi);

    unsigned long int precision = idm.getRequiredPrecision(base, targetDigits);

    std::vector<unsigned long int> result;
    result = calc.convertNumberToBase(pi, base, targetDigits, precision);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    QString fn = QString::number(base) + "-" + QString::number(targetDigits) + QString(".dec");

    dm.writeDigitsToFile(fn, result);

    // Convert duration to string
    std::string timeTakenSeconds = std::to_string(duration.count()) + " seconds";

    Log() << "executeItem completed. Time taken is " + QString(timeTakenSeconds.c_str());
}

void queueManager::createImageSeries()
{
    QString fileName = "11-2073600.dec";
    dataManager dm;

    std::vector<unsigned long> digits;
    dm.readDigitsFromFile(fileName, digits);

    Log() << "Loaded digits.";

    imageManager im;
    im.createImageSeries(digits, 11, 11, 1920, 1080);

    Log() << "createImageSeries finished";
}
