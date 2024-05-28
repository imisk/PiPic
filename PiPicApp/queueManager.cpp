#include "queueManager.h"
#include <QDebug>
#include "dataManager.h"
#include "logger.h"
#include <imageManager.h>
#include <queueItemWorker.h>

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
    QString fileName = "25-200000.dec";
    dataManager dm;

    std::vector<unsigned long> digits;
    dm.readDigitsFromFile(fileName, digits);

    Log() << "Loaded digits.";

    imageManager im;
    im.createImageSeries(digits, 25, 25, 800, 1080);

    Log() << "createImageSeries finished";
}

void queueManager::updateDigitProgress(int curDigit)
{
    emit forwardDigitProgress(curDigit);
}

void queueManager::setupWorkerAndThread(queueItemWorker* worker, QThread* thread) {}
