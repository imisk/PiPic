#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QReadWriteLock>
#include <QString>
#include <vector>

struct appSettings
{
    int minBase;     // the minimum base at which to start calcs
    int maxBase;     //maximum base to do calcs. stops when reached.
    int threadCount; //how many threads to launch when running
};

/*
 * Writes and reads objects to/from disk. 
 * Related only to data of save states and calculation.
 */
#include <fstream>
class dataManager
{
public:
    dataManager();

    void writeDigitsToFile(QString &filename, std::vector<unsigned long> digits, int base);

    void readDigitsFromFile(QString &fileName, std::vector<unsigned long> &retDigits);

    std::vector<int> findFinishedDigits();

    void createABCLogs();

    void loadABCLogs(std::vector<int> &retFinished, std::vector<int> &retRunning);

    void saveABCLogs(std::vector<int> &retFinished, std::vector<int> &retRunning);

    void saveSettings();

    void loadSettings();

private:
    template<typename T>
    void dataWrite(std::ofstream &fs, T &val);

    template<typename T>
    void dataRead(std::ifstream &fr, T &val);

    unsigned char writeHeader(std::ofstream &fs, int base);

    unsigned char readHeader(std::ifstream &fr, int &retBase);

    int currentlyLoadedAbcLog
        = 0; //if 0 is loaded, 1 should be saved next, etc. values can be 0,1,2==A,B,C

    QReadWriteLock readWriteLock;

    appSettings settings;
};

#endif  // DATAMANAGER_H
