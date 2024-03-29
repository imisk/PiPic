#include "logStream.h"
#include <QIODevice>
#include <QDebug>
#include "mainWindow.h"

MainWindow* mwp;

LogStream::LogStream()
    : stream_(&buffer_, QIODevice::WriteOnly)
{}

LogStream::~LogStream()
{
    if (mwp)
    {
        emit mwp->logMessageReceived(buffer_);
        buffer_.clear();
    }
}
