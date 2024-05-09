#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QColor>
#include <vector>

class imageManager
{
public:
    imageManager();

    std::vector<QColor> assignColoursToDigits(int base, int bins, std::vector<QColor> palette);
};

#endif // IMAGEMANAGER_H
