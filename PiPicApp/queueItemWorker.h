#ifndef QUEUEITEMWORKER_H
#define QUEUEITEMWORKER_H

#include <QObject>

class queueItemWorker : public QObject
{
    Q_OBJECT
public:
    explicit queueItemWorker(QObject *parent = nullptr);

public slots:

    void executeItem();

    void digitCountReceived(int);

signals:
    void workFinished();

    void digitProgress(int);
};

#endif // QUEUEITEMWORKER_H
