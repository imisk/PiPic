#ifndef DATAMANAGER_H
#define DATAMANAGER_H

/*
 * Writes and reads objects to/from disk. 
 * Related only to data of save states and calculation.
 */
#include <fstream>
class datamanager
{
public:
    datamanager();

private:
    template<typename T>
    void dataWrite(std::fstream &fs, T &val);

    template<typename T>
    void dataRead(std::fstream &fr, T &val);
};

#endif  // DATAMANAGER_H
