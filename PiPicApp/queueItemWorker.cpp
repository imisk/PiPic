#include "queueItemWorker.h"
#include <QDebug>
#include <QThread>
#include <calculator.h>
#include <dataManager.h>
#include <inputDataManager.h>
#include <logger.h>

queueItemWorker::queueItemWorker(dataManager* dm, QObject* parent)
    : QObject{parent}
    , dataMngr(dm)
{
    
}

void queueItemWorker::executeItem()
{
    Log() << "Starting calculation";

    //int base = 11;
    //size_t targetDigits = 20000000;
    size_t targetDigits = 3000000;

    calculator calc;
    inputDataManager idm;

    connect(&calc, &calculator::digitUpdate, this, &queueItemWorker::digitCountReceived);

    for (int base = 114; base < 120; base++) {
        Log() << "Base: " << base << " Target decimal count: " << targetDigits;

        int requiredPiDecimals = idm.getRequiredPiDecimalDigits(base, targetDigits);

        std::string pi = "";

        idm.loadPiFromDisk1Billion(static_cast<size_t>(requiredPiDecimals), pi);

        unsigned long int precision = idm.getRequiredPrecision(base, targetDigits);

        std::vector<unsigned long int> result;

        auto start = std::chrono::high_resolution_clock::now();

        result = calc.convertNumberToBase(pi, base, targetDigits, precision);

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        QString fn = QString::number(base) + "-" + QString::number(targetDigits) + QString(".dec");

        dataMngr->writeDigitsToFile(fn, result, base);

        // Convert duration to string
        std::string timeTakenSeconds = std::to_string(duration.count()) + " seconds";

        Log() << "Seconds taken: " << QString(timeTakenSeconds.c_str());
    }

    //----

    emit workFinished();
}

void queueItemWorker::digitCountReceived(int v)
{
    emit digitProgress(v);
}
