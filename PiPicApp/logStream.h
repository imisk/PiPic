#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include <QString>
#include <QStringBuilder>
#include <QTextStream>

class MainWindow;

extern MainWindow* mwp;

class LogStream
{
public:
    LogStream();
    ~LogStream();

    template<typename T>
    LogStream& operator<<(const T& value)
    {
        stream_ << value;
        return *this;
    }

private:
    QString buffer_;
    QTextStream stream_;
};

#endif // LOGSTREAM_H
