#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <map>
#include <QString>

class calculator
{
public:
    calculator();

    void accuracyTrial1();

    void accuracyTrial2a();

    void accuracyTrial2b();

    //Calculate the minimum number of digits required to identify the digit from the remainder
    std::map<QString, int> getDigitDecimals(int base);

};

#endif // CALCULATOR_H
