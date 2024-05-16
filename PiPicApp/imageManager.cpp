#include "imageManager.h"
#include <QColor>
#include <QDebug>
#include <QImage>
#include <logger.h>
#include <paletteManager.h>
#include <vector>

imageManager::imageManager() {}

void imageManager::createImageSeries(
    std::vector<unsigned long> digits, size_t base, size_t bins, int width, int height)
{
    paletteManager pm;
    auto pal = pm.createColourWheel_BlackAndWhiteNoRedRight();

    auto colours = assignColoursToDigits(base, bins, pal);

    int x = 0;
    int y = 0;

    QString fileNameBase = "images/" + QString::number(base) + "_" + QString::number(width) + "_"
                           + QString::number(height) + "_";

    QImage image = QImage(width, height, QImage::Format_RGB32);

    int curImageCount = 1;

    for (size_t i = 0; i < digits.size(); i++) {
        auto curDigit = digits[i];

        auto color = colours[curDigit];

        image.setPixel(x, y, color.rgb());

        ++x;
        if (x > width) {
            x = 0;
            ++y;
        }

        if (y > height) {
            QString filePath = fileNameBase + QString::number(curImageCount) + ".png";

            if (!image.save(filePath, "PNG")) {
                Log() << "Failed to save the image.";
            }
            y = 0;

            curImageCount++;
            image = QImage(width, height, QImage::Format_RGB32);
        }
    }

    if (y > 0 || x > 0) {
        QString filePath = fileNameBase + QString::number(curImageCount) + ".png";

        if (!image.save(filePath, "PNG")) {
            Log() << "Failed to save the image.";
        }
    }
}

std::vector<QColor> imageManager::assignColoursToDigits(size_t base,
                                                        size_t bins,
                                                        std::vector<QColor> palette)
{
    /*returns a vector of QColor so that each index corresponds to a digit

    bins is how many different colours to have. if you use "4" then the palette will be split into 4 colours
    so the lowest 25% of the digits will have the same colour.

    if bins is higher than palette.size() then multiple digits will share the same colour in some cases.
    the maximum value of bins can be equal to base.

    the function first assigns colours to the bins vector, which will have size == bins
    then, these colours are assigned to the return array, and split evenly among the digits.
    */

    if (bins > base)
        bins = base;

    if (bins > palette.size())
        bins = palette.size();

    qDebug() << "palette.size() = " << palette.size();

    //step is how many pixels to move forward for each bin
    double binStep = static_cast<double>(palette.size() - 1) / static_cast<double>(bins - 1);
    qDebug() << "binStep = " << binStep;
    double curPalettePos = 0.0;

    std::vector<QColor> binsPalette;

    for (size_t curBinPos = 0; curBinPos < bins; curBinPos++) {
        qDebug() << "--------- curPalettePos = " << curPalettePos;
        size_t cpp = static_cast<size_t>(curPalettePos);
        qDebug() << "cpp = " << cpp;

        if (cpp > palette.size() - 1)
            cpp = palette.size() - 1;

        binsPalette.push_back(palette[cpp]);

        curPalettePos += binStep;
    }

    //now assign bins to digits
    double tgtStep = static_cast<double>(binsPalette.size()) / static_cast<double>(base);

    double curBinPos = 0.0;

    std::vector<QColor> ret;

    qDebug() << "binsPalette.size = " << binsPalette.size();

    for (size_t i = 0; i < base; i++) {
        size_t cbp = static_cast<size_t>(curBinPos);

        if (cbp > binsPalette.size() - 1)
            cbp = binsPalette.size() - 1;

        qDebug() << "curBinPos = " << curBinPos << " __ cbp = " << cbp;

        ret.push_back(binsPalette[cbp]);

        curBinPos += tgtStep;
    }

    return ret;
}
