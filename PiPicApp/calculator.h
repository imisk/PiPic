#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>
#include <map>
#include <vector>

class calculator : public QObject
{
    Q_OBJECT
public:
    calculator(QObject *parent = nullptr);

    void gmpTrial1();

    void gmpTrial2();

    void gmpTrial3();

    //Calculate the minimum number of digits required to identify the digit from the remainder
    std::map<QString, int> getDigitDecimals(int base);

    std::vector<unsigned long int> convertNumberToBase(std::string &inputNumber,
                                                       int base,
                                                       size_t maxDigits,
                                                       unsigned long int precision);

signals:

    void digitUpdate(int digitCount);
};

#endif // CALCULATOR_H
