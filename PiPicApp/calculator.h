#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <map>
#include <vector>

class calculator
{
public:
    calculator();

    void gmpTrial1();

    void gmpTrial2();

    void gmpTrial3();

    //Calculate the minimum number of digits required to identify the digit from the remainder
    std::map<QString, int> getDigitDecimals(int base);

    std::vector<unsigned long int> convertNumberToBase(std::string &inputNumber,
                                                       int base,
                                                       size_t maxDigits);
};

#endif // CALCULATOR_H
