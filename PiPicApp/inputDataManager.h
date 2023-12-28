#ifndef INPUTDATAMANAGER_H
#define INPUTDATAMANAGER_H

#include <QString>

class inputDataManager
{
public:
    inputDataManager();

    //Loads Pi value from large text file
    void loadPiFromDisk1Million(size_t maxDigitsToLoad, QString &retNumber);
};

#endif // INPUTDATAMANAGER_H
