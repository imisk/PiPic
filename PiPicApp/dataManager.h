#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <vector>

/*
 * Writes and reads objects to/from disk. 
 * Related only to data of save states and calculation.
 */
#include <fstream>
class datamanager
{
public:
    datamanager();

    void writeDigitsToFile(QString &filename, std::vector<unsigned long> digits);

private:
    template<typename T>
    void dataWrite(std::ofstream &fs, T &val);

    template<typename T>
    void dataRead(std::fstream &fr, T &val);
};

#endif  // DATAMANAGER_H
