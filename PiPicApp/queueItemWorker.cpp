#include "queueItemWorker.h"
#include <QDebug>
#include <QThread>
#include <calculator.h>
#include <dataManager.h>
#include <inputDataManager.h>
#include <logger.h>

queueItemWorker::queueItemWorker(QObject *parent)
    : QObject{parent}
{
    
}

void queueItemWorker::executeItem()
{
    auto start = std::chrono::high_resolution_clock::now();

    Log() << "Starting calculation";

    int base = 11;
    size_t targetDigits = 20000000;

    Log() << "Base: " << base << " Target decimal count: " << targetDigits;

    calculator calc;
    inputDataManager idm;
    dataManager dm;

    connect(&calc, &calculator::digitUpdate, this, &queueItemWorker::digitCountReceived);

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
}

void queueItemWorker::digitCountReceived(int v)
{
    emit digitProgress(v);
}
