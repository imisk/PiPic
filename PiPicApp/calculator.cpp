#include "calculator.h"
#include "logger.h"
#include <set>

calculator::calculator()
{

}

void calculator::accuracyTrial1()
{

}

std::map<QString, int> calculator::getDigitDecimals(int base)
{


    std::map<QString, int> ret;

    if (base < 1)
    {
        //todo: exception
    }

    bool finished = false;



    double db = static_cast<double>(base);

    std::set<QString> remaindersUnpadded;

    for (int i = 1; i < base; i++)
    {
        double curRemainder = static_cast<double>(i) / db;

        QString r = QString::number(curRemainder);

        r.remove(0,2);

        if (remaindersUnpadded.find(r) != remaindersUnpadded.end())
        {
            //todo: throw exception. the base is too large to represent all remainders with double precision division
        }

        remaindersUnpadded.insert(r);
    }

    //add zeros to reach maximum length required, so all strings are equal length
    long long maxLengthFound = 0;

    for (auto& r : remaindersUnpadded)
    {
        if (r.length() > maxLengthFound) maxLengthFound = r.length();
    }

    std::vector<QString> remainders;

    for (const QString& value : remaindersUnpadded)
    {
        QString paddedValue = value;

        while (paddedValue.length() < maxLengthFound)
        {
            paddedValue.append('0');
        }

        remainders.push_back(paddedValue);
    }

    int curDecimalCount = 1;

    ret.clear();

    while (!finished)
    {

        for (size_t i = 0; i < remainders.size(); i++)
        {
            auto& r = remainders[i];

            QString shortened = r.left(curDecimalCount);

            if (ret.find(shortened) != ret.end())
            {
                curDecimalCount++;
                ret.clear();
                break;
            }
            else
            {
                ret.insert({shortened, i+1});
            }
        }

        if (ret.size() > 0)
        {
            finished = true;
        }
    }

    for (auto& i : ret)
    {
        Log() << "str = " << i.first << " _ val = " << i.second;
    }


    return ret;
}
