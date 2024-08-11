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
    void executeItem(dataManager* dm);

    void createImageSeries();

signals:

    void forwardDigitProgress(int curDigit);

public slots:

    void updateDigitProgress(int curDigit);

private:
    void setupWorkerAndThread(queueItemWorker* worker, QThread* thread);
};

#endif // QUEUEMANAGER_H
