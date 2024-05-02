#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H
#include <QColor>

class paletteManager
{
public:
    paletteManager();

    void createColourWheel();

    void createColourWheel_WithBlackAndWhite();

    std::vector<QColor> createColourWheel_BlackAndWhiteNoRedRight();
};

#endif // PALETTEMANAGER_H
