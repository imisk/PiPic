#include "paletteManager.h"
#include <QColor>
#include <QDebug>
#include <QImage>
#include <vector>
paletteManager::paletteManager()
{
    
}

void paletteManager::createColourWheel()
{
    //brightest colours only
    int r = 255;
    int g = 0;
    int b = 0;

    std::vector<QColor> vec;
    QColor col;

    for (g = 0; g < 256; g++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    --g;

    for (r = 255; r >= 0; r--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r++;

    for (b = 0; b < 256; b++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b--;

    for (g = 255; g >= 0; g--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    g++;

    for (r = 0; r < 256; r++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r--;

    for (b = 255; b >= 0; b--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b++;

    qDebug() << "Total colors = " << vec.size();

    int height = 400;

    // Create a new QImage with the specified dimensions
    QImage image(vec.size() + 1, height, QImage::Format_RGB32);

    for (int x = 0; x < (int) vec.size(); x++) {
        for (int y = 0; y < height; y++) {
            auto color = vec[x];

            image.setPixel(x, y, color.rgb());
        }
    }

    QString filePath = "rgbyeeey.png";

    if (!image.save(filePath, "PNG")) {
        qDebug() << "Failed to save the image.";
    }

    qDebug() << "Done";
}

void paletteManager::createColourWheel_WithBlackAndWhite()
{
    //brightest colours only, with black and white
    int r = 255;
    int g = 0;
    int b = 0;

    /*
255,0,0
255,255,0 g++
0,255,0 r--
0,255,255 b++
0,0,255 g--
255,0,255 r++
255,0,0 b--*/

    std::vector<QColor> vec;
    QColor col;

    for (g = 0; g < 256; g++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    --g;

    for (r = 255; r >= 0; r--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r++;

    for (b = 0; b < 256; b++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b--;

    //go to white
    for (r = 0; r < 256; r++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r++;

    //go to black
    for (r = 255; r >= 0; r--) {
        g = r;
        b = r;
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r = 0;
    g = 0;

    for (b = 0; b < 256; b++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b--;

    for (r = 0; r < 256; r++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r--;

    for (b = 255; b >= 0; b--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b++;

    qDebug() << "Total colors = " << vec.size();

    int height = 400;

    // Create a new QImage with the specified dimensions
    QImage image(vec.size() + 1, height, QImage::Format_RGB32);

    for (int x = 0; x < (int) vec.size(); x++) {
        for (int y = 0; y < height; y++) {
            auto color = vec[x];

            image.setPixel(x, y, color.rgb());
        }
    }

    QString filePath = "rgbyeeey_bw.png";

    if (!image.save(filePath, "PNG")) {
        qDebug() << "Failed to save the image.";
    }

    qDebug() << "Done";
}

std::vector<QColor> paletteManager::createColourWheel_BlackAndWhiteNoRedRight()
{
    //it might be a good idea not to have the red colour loop, so that we know where there is a hard cutoff
    //between very high and very low digits

    int r = 255;
    int g = 0;
    int b = 0;

    /*
255,0,0
255,255,0 g++
0,255,0 r--
0,255,255 b++
255,255,255 r++
0,0,0 rgb--
0,0,255 b++
255,0,255 r++*/

    std::vector<QColor> vec;
    QColor col;

    for (g = 0; g < 256; g++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    --g;

    for (r = 255; r >= 0; r--) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r++;

    for (b = 0; b < 256; b++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b--;

    //go to white
    for (r = 0; r < 256; r++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r++;

    //go to black
    for (r = 255; r >= 0; r--) {
        g = r;
        b = r;
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r = 0;
    g = 0;

    for (b = 0; b < 256; b++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    b--;

    for (r = 0; r < 256; r++) {
        qDebug() << r << "," << g << "," << b;
        col = QColor(r, g, b, 255);
        vec.push_back(col);
    }
    r--;

    //    for (b = 255; b >= 0; b--)
    //    {
    //        qDebug() << r << "," << g << "," << b;
    //        col = QColor(r,g,b,255);
    //        vec.push_back(col);
    //    }
    //    b++;

    qDebug() << "Total colors = " << vec.size();

    int height = 400;

    // Create a new QImage with the specified dimensions
    QImage image(vec.size() + 1, height, QImage::Format_RGB32);

    for (int x = 0; x < (int) vec.size(); x++) {
        for (int y = 0; y < height; y++) {
            auto color = vec[x];

            image.setPixel(x, y, color.rgb());
        }
    }

    QString filePath = "rgbyeeey_bwnr.png";

    if (!image.save(filePath, "PNG")) {
        qDebug() << "Failed to save the image.";
    }

    qDebug() << "Done";

    return vec;
}
