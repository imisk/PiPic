#ifndef QUEUEITEMWORKER_H
#define QUEUEITEMWORKER_H

#include <QObject>
#include <dataManager.h>

class queueItemWorker : public QObject
{
    Q_OBJECT
public:
    explicit queueItemWorker(dataManager* dm, QObject* parent = nullptr);

public slots:

    void executeItem();

    void digitCountReceived(int);

signals:
    void workFinished();

    void digitProgress(int);

private:
    dataManager* dataMngr;
};

#endif // QUEUEITEMWORKER_H
