#ifndef INPUTDATAMANAGER_H
#define INPUTDATAMANAGER_H

#include <QString>
#include <vector>

class inputDataManager
{
public:
    inputDataManager();

    //Loads Pi value from large text file
    void loadPiFromDisk1Million(size_t maxDigitsToLoad, QString &retNumber);

    //Load known digits for accuracy verification testing. File text format "123,456,223"
    std::vector<int> loadKnownCalculation(std::string &filePath);
};

#endif // INPUTDATAMANAGER_H
