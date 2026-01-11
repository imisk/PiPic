#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QObject>
#include <QThread>
#include <queueItemWorker.h>
class queueManager : public QObject
{
    Q_OBJECT

public:
    explicit queueManager(QObject* parent = nullptr);

    ~queueManager();
    void executeItem();

    void initializeQueue(dataManager* ndm);

    void createImageSeries();

signals:

    void forwardDigitProgress(int curDigit);

public slots:

    void updateDigitProgress(int curDigit);

    void oneItemFinished();

private:
    void setupWorkerAndThread(queueItemWorker* worker, QThread* thread);

    dataManager* dm{nullptr};
};

#endif // QUEUEMANAGER_H
