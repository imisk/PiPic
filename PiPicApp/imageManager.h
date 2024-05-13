#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QColor>
#include <vector>

class imageManager
{
public:
    imageManager();

    void createImageSeries(
        std::vector<unsigned long> digits, size_t base, size_t bins, int width, int height);
    /*
    palette : the colours you want to use
      
    bins: how many different colours you want to have. can be equal to base, or less than base.
    if base is higher than number of colours, some digits will have the same colour assigned.  */
    std::vector<QColor> assignColoursToDigits(size_t base, size_t bins, std::vector<QColor> palette);
};

#endif // IMAGEMANAGER_H
