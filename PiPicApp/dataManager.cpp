#include "dataManager.h"
#include "logger.h"
#include <fstream>
#include <vector>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QReadWriteLock>
#include <QStringList>

dataManager::dataManager() {}

void dataManager::writeDigitsToFile(QString &filename, std::vector<unsigned long> digits, int base)
{
    std::ofstream file;

    // Open the file in write mode
    file.open(filename.toStdString(), std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        Log() << "Error: Could not open the file.";
        return;
    }

    unsigned char digitSize = writeHeader(file, base);

    size_t ds = digits.size();

    dataWrite(file, ds);

    for (unsigned long digit : digits) {
        if (digitSize == 0) {
            unsigned char val = static_cast<unsigned char>(digit);
            dataWrite(file, val);
        } else if (digitSize == 1) {
            unsigned short int val = static_cast<unsigned short int>(digit);
            dataWrite(file, val);
        } else if (digitSize == 2) {
            unsigned int val = static_cast<unsigned int>(digit);
            dataWrite(file, val);
        } else {
            dataWrite(file, digit);
        }
    }

    file.close();

    Log() << "writeDigitsToFile - Finished writing.";
}

void dataManager::readDigitsFromFile(QString &fileName, std::vector<unsigned long> &retDigits)
{
    std::ifstream file;
    file.open(fileName.toStdString(), std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        Log() << "Error: readDigitsFromFile - could not open the file.";
        return;
    }

    int base = -1;

    unsigned char digitSize = readHeader(file, base);

    if (digitSize == 250) {
        //todo : 250 should be constexpr value
        Log() << "Error : file header corrupted.";
        return;
    }

    size_t count;
    dataRead(file, count);

    for (size_t i = 0; i < count; i++) {
        if (digitSize == 0) {
            unsigned char val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned long>(val));
        } else if (digitSize == 1) {
            unsigned short int val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned short int>(val));
        } else if (digitSize == 2) {
            unsigned int val;
            dataRead(file, val);
            retDigits.push_back(static_cast<unsigned int>(val));
        } else {
            unsigned long decimal;
            dataRead(file, decimal);
            retDigits.push_back(decimal);
        }
    }

    file.close();
}

std::vector<int> dataManager::findFinishedDigits()
{
    QString folderPath
        = "/home/ivan/dev/pipic/build-PiPic-Desktop_Qt_6_5_2_GCC_64bit-Release/PiPicApp/1/";

    QDir folder(folderPath);

    folder.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QStringList filters;
    filters << "*.dec";
    folder.setNameFilters(filters);

    QStringList decFiles;

    std::vector<int> ret;

    ret.push_back(11);

    foreach (QFileInfo fileInfo, folder.entryInfoList(filters, QDir::Files)) {
        decFiles.append(fileInfo.absoluteFilePath());

        qDebug() << "fn = " << fileInfo.fileName();

        std::ifstream file;
        file.open(fileInfo.absoluteFilePath().toStdString(), std::ios::binary | std::ios::in);

        if (!file.is_open()) {
            Log() << "Error: readDigitsFromFile - could not open the file.";
            return ret;
        }

        int base = -1;

        unsigned char digitSize = readHeader(file, base);

        if (digitSize == 250) {
            //todo : 250 should be constexpr value
            Log() << "Error : file header corrupted.";
        } else {
            qDebug() << "adding base = " << base;
            ret.push_back(base);
        }

        file.close();
    }

    return ret;
}

void dataManager::createABCLogs()
{
    std::ofstream file;
    auto fin = findFinishedDigits();

    std::vector<int> curProc;

    currentlyLoadedAbcLog = 0;
    saveABCLogs(fin, curProc);

    currentlyLoadedAbcLog = 1;
    saveABCLogs(fin, curProc);

    currentlyLoadedAbcLog = 2;
    saveABCLogs(fin, curProc);
}

void dataManager::loadABCLogs(std::vector<int> &retFinished, std::vector<int> &retRunning)
{
    std::tm currentMaxDate = {};
    currentMaxDate.tm_year = 0;
    currentMaxDate.tm_mon = 0;
    currentMaxDate.tm_mday = 1;

    std::ifstream file;
    readWriteLock.lockForRead();

    for (int idx = 0; idx <= 2; idx++) {
        QString filename = "";
        if (idx == 0) {
            filename = "finLogA.log";
        } else if (idx == 1) {
            filename = "finLogB.log";
        } else if (idx == 2) {
            filename = "finLogC.log";
        }

        file.open(filename.toStdString(), std::ios::binary | std::ios::in);

        if (!file.is_open()) {
            Log() << "Error: Could not open the ABC log file: " << filename;
            return;
        }

        size_t finCount;
        dataRead(file, finCount);

        std::vector<int> fin(finCount);
        for (int &d : fin) {
            dataRead(file, d);
        }

        size_t curCount;

        dataRead(file, curCount);

        std::vector<int> curRunning(curCount);

        if (curCount > 0) {
            for (int &d : curRunning) {
                dataRead(file, d);
            }
        }

        int yr, mon, mday, hour, min;
        dataRead(file, yr);
        dataRead(file, mon);
        dataRead(file, mday);
        dataRead(file, hour);
        dataRead(file, min);

        std::tm readDate = {};
        readDate.tm_year = yr - 1900;
        readDate.tm_mon = mon - 1;
        readDate.tm_mday = mday;
        readDate.tm_hour = hour;
        readDate.tm_min = min;
        readDate.tm_sec = 0;

        time_t readTime = std::mktime(&readDate);
        time_t currentTime = std::mktime(&currentMaxDate);

        if (readTime > currentTime) {
            currentMaxDate = readDate;

            retFinished = fin;
            retRunning = curRunning;

            currentlyLoadedAbcLog = idx;
        }

        file.close();
    }
    readWriteLock.unlock();
}

void dataManager::saveABCLogs(std::vector<int> &retFinished, std::vector<int> &retRunning)
{
    std::ofstream file;

    QString filename = "";

    if (currentlyLoadedAbcLog == 0) {
        filename = "finLogA.log";
    } else if (currentlyLoadedAbcLog == 1) {
        filename = "finLogB.log";
    } else if (currentlyLoadedAbcLog == 2) {
        filename = "finLogC.log";
    }

    readWriteLock.lockForWrite();

    file.open(filename.toStdString(), std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        Log() << "Error: Could not open the file.";
        return;
    }
    size_t finCount = retFinished.size();

    dataWrite(file, finCount); //count of finished

    //list of finished
    for (int d : retFinished) {
        dataWrite(file, d);
    }

    size_t curCount = retRunning.size();

    dataWrite(file, curCount);

    if (curCount > 0) {
        for (int d : retRunning) {
            dataWrite(file, d);
        }
    }

    //write current time
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::gmtime(&now_c);

    int yr = now_tm.tm_year + 1900;
    int mon = now_tm.tm_mon + 1;

    dataWrite(file, yr);
    dataWrite(file, mon);
    dataWrite(file, now_tm.tm_mday);
    dataWrite(file, now_tm.tm_hour);
    dataWrite(file, now_tm.tm_min);

    file.close();

    readWriteLock.unlock();
}

unsigned char dataManager::writeHeader(std::ofstream &fs, int base)
{
    uchar id = 0;

    if (base <= std::numeric_limits<unsigned char>::max()) {
        id = 0; //use bytes
    } else if (base <= std::numeric_limits<unsigned short int>::max()) {
        id = 1; //use shorts
    } else if (base <= std::numeric_limits<unsigned int>::max()) {
        id = 2; //use ints
    } else {
        id = 3; //use longs
    }

    uchar n = 18;
    dataWrite(fs, n);

    n = 11;
    dataWrite(fs, n);

    n = 21;
    dataWrite(fs, n);

    dataWrite(fs, id);

    dataWrite(fs, base);

    return id;
}

unsigned char dataManager::readHeader(std::ifstream &fr, int &retBase)
{
    uchar n1;
    dataRead(fr, n1);

    uchar n2;
    dataRead(fr, n2);

    uchar n3;
    dataRead(fr, n3);

    uchar id;
    dataRead(fr, id);

    if (n1 != 18 || n2 != 11 || n3 != 21) {
        return 250; //todo: add exception
    }

    dataRead(fr, retBase);

    return id;
}

template<typename T>
void dataManager::dataWrite(std::ofstream &fs, T &val)
{
    fs.write(reinterpret_cast<char *>(&val), sizeof(val));
}

template<typename T>
void dataManager::dataRead(std::ifstream &fr, T &val)
{
    fr.read(reinterpret_cast<char *>(&val), sizeof(val));
}
