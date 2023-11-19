#include "calculator.h"
#include "bhimInteger.h"
#include "logger.h"
#include <set>

calculator::calculator()
{

}

void calculator::accuracyTrial1()
{
    //this function calculates Pi to pow digits in sbase base.
    // pow is the digit count we will be calculating up to

    BhimInteger bpow("6");

    std::string sbase = "16";
    BhimInteger bbase(sbase);

    BhimInteger result;

    result = result.powBhimInteger(sbase, bpow);

    // this loop is slightly faster than powBhimInteger, we should use it

    //  for (int curPow = 0; curPow < pow - 1; ++curPow) {
    //    if (curPow % 100 == 0) {
    //      Log() << "cp = " << curPow << '\n';
    //    }
    //  }

    Log() << "start result = " << result.toQString();

    BhimInteger pi("38478945");

    //    BhimInteger pi(
    //        "314159265358979323846264338327950288419716939937510582097494459230781640"
    //        "628620899862803482534211706798214808651328230664709384460955058223172535"
    //        "940812848111745028410270193852110555964462294895493038196442881097566593"
    //        "344612847564823378678316527120190914564856692346034861045432664821339360"
    //        "726024914127372458700660631558817488152092096282925409171536436789259036"
    //        "001133053054882046652138414695194151160943305727036575959195309218611738"
    //        "193261179310511854807446237996274956735188575272489122793818301194912983"
    //        "367336244065664308602139494639522473719070217986094370277053921717629317"
    //        "675238467481846766940513200056812714526356082778577134275778960917363717"
    //        "872146844090122495343014654958537105079227968925892354201995611212902196"
    //        "086403441815981362977477130996051870721134999999837297804995105973173281"
    //        "609631859502445945534690830264252230825334468503526193118817101000313783"
    //        "875288658753320838142061717766914730359825349042875546873115956286388235"
    //        "37875937519577818577805321712268066130019278766111959092164201989");

    if (static_cast<size_t>(bpow.to_int()) > pi.getDigitCount() - 1) {
        Log() << "Error : pow > pi digit count \n";
        return;
    }

    Log() << "Input pi digit count = " << pi.getDigitCount();

    size_t digitsToRemove = pi.getDigitCount() - 1;

    Log() << "digitsToRemove = " << digitsToRemove;

    BhimInteger tenToThePower = tenToThePower.powBhimInteger(10, digitsToRemove);

    BhimInteger divisor = bbase * tenToThePower;

    Log() << "divisor = " << divisor.toQString();

    auto pi_mul_start = pi * result;

    Log() << "pi_mul_start = " << pi_mul_start.toQString();

    pi_mul_start.setLastDigitsToZero(digitsToRemove);

    Log() << "pi_mul_start 0 = " << pi_mul_start.toQString();

    bool finished = false;

    BhimInteger quotient, r2w, digit;

    while (!finished) {
        quotient = pi_mul_start / divisor;

        Log() << "quotient = " << quotient.toQString();

        r2w = quotient * divisor;

        Log() << "r2w = " << r2w.toQString();

        digit = pi_mul_start - r2w;
        digit = digit / tenToThePower;

        Log() << "-------- digit = " << digit.toQString();

        pi_mul_start = pi_mul_start / bbase;

        pi_mul_start.setLastDigitsToZero(digitsToRemove);

        Log() << "pi_mul_start end = " << pi_mul_start.toQString();

        if (pi_mul_start.getDigitCount() <= digitsToRemove) {
            finished = true;
        }
    }

    //    size_t curLength = pi_mul_start.getDigitCount();

    //    size_t remainingDigits = curLength - digitsToRemove;

    //    pi_mul_start.removeDigitsAfterIdx(remainingDigits);

    //    Log() << "pi_mul_start 2 = " << QString(pi_mul_start.toString().c_str()) << '\n';

    //    BhimInteger quotient, r2w, digit;

    //    //----

    //    bool finished = false;

    //    Log() << "\n\nDIGITS OUTPUT: \n";

    //    std::string resultReversed = "";

    //    while (!finished) {
    //        quotient = pi_mul_start / bbase;
    //        // cout << "r2 = " << quotient << '\n';
    //        r2w = quotient * bbase;
    //        // cout << "r2w = " << r2w << '\n';
    //        digit = pi_mul_start - r2w;
    //        // cout << "digit *********** = " << digit << '\n';

    //        char digitChar = decimalToHex(digit.to_int());

    //        resultReversed.push_back(digitChar);

    //        pi_mul_start = quotient;

    //        if (quotient == 0) {
    //            finished = true;
    //        }
    //    }

    //    Log() << "reversed = " << QString(resultReversed.c_str()) << "\n\n";
    //    reverseString(resultReversed);
    //    Log() << "normal = " << QString(resultReversed.c_str()) << '\n';

    //    Log() << '\n';
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
