#include "queueManager.h"
#include <QDebug>
#include "dataManager.h"
#include "logger.h"
#include <chrono>
#include <imageManager.h>
#include <queueItemWorker.h>
#include <string>
queueManager::queueManager(QObject* parent)
    : QObject(parent)
{}

queueManager::~queueManager() {}

void queueManager::executeItem()
{
    QThread* thread = new QThread;
    queueItemWorker* worker = new queueItemWorker;

    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &queueItemWorker::executeItem);
    connect(worker, &queueItemWorker::workFinished, thread, &QThread::quit);
    connect(worker, &queueItemWorker::workFinished, worker, &queueItemWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    auto cv = connect(worker,
                      &queueItemWorker::digitProgress,
                      this,
                      &queueManager::updateDigitProgress,
                      Qt::DirectConnection);

    qDebug() << "cv = " << cv;

    thread->start();
}

void queueManager::createImageSeries()
{
    QString fileName = "11-2073600.dec";
    dataManager dm;

    std::vector<unsigned long> digits;
    dm.readDigitsFromFile(fileName, digits);

    Log() << "Loaded digits.";

    imageManager im;
    im.createImageSeries(digits, 11, 11, 800, 1080);

    Log() << "createImageSeries finished";
}

void queueManager::updateDigitProgress(int curDigit)
{
    emit forwardDigitProgress(curDigit);
}

void queueManager::setupWorkerAndThread(queueItemWorker* worker, QThread* thread) {}
