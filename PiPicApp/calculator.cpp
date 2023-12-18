#include "calculator.h"
#include <QString>
#include "../../gmp_build/gmp.h"
#include "bhimInteger.h"
#include "logger.h"
#include "utility.h"
#include <set>
#include <vector>

calculator::calculator() {}

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
}

void calculator::accuracyTrial2a()
{
    //this function calculates Pi to pow digits in sbase base.
    // pow is the digit count we will be calculating up to

    BhimInteger bpow("20");

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

    BhimInteger pi("314159265358979323846264");

    //    BhimInteger pi("314159265358979323846264338327950288419716939937510582097494459230781640"
    //                   "628620899862803482534211706798214808651328230664709384460955058223172535"
    //                   "940812848111745028410270193852110555964462294895493038196442881097566593"
    //                   "344612847564823378678316527120190914564856692346034861045432664821339360"
    //                   "726024914127372458700660631558817488152092096282925409171536436789259036"
    //                   "001133053054882046652138414695194151160943305727036575959195309218611738"
    //                   "193261179310511854807446237996274956735188575272489122793818301194912983"
    //                   "367336244065664308602139494639522473719070217986094370277053921717629317"
    //                   "675238467481846766940513200056812714526356082778577134275778960917363717"
    //                   "872146844090122495343014654958537105079227968925892354201995611212902196"
    //                   "086403441815981362977477130996051870721134999999837297804995105973173281"
    //                   "609631859502445945534690830264252230825334468503526193118817101000313783"
    //                   "875288658753320838142061717766914730359825349042875546873115956286388235"
    //                   "37875937519577818577805321712268066130019278766111959092164201989");

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

    QString resultReversed;

    while (!finished) {
        quotient = pi_mul_start / divisor;

        //Log() << "quotient = " << quotient.toQString();

        r2w = quotient * divisor;

        //Log() << "r2w = " << r2w.toQString();

        digit = pi_mul_start - r2w;
        digit = digit / tenToThePower;

        char digitChar = decimalToHex(digit.to_int());

        resultReversed.push_back(digitChar);

        Log() << "-------- digit = " << digit.toQString();

        pi_mul_start = pi_mul_start / bbase;

        pi_mul_start.setLastDigitsToZero(digitsToRemove);

        //Log() << "pi_mul_start end = " << pi_mul_start.toQString();

        if (pi_mul_start.getDigitCount() <= digitsToRemove) {
            finished = true;
        }
    }

    reverseString(resultReversed);

    Log() << "normal = " << resultReversed;
}

void calculator::accuracyTrial2b()
{
    //Trying out BhimInteger

    BhimInteger bpow("11");

    std::string sbase = "16";
    BhimInteger bbase(sbase);

    BhimInteger result;

    result = result.powBhimInteger(sbase, bpow);

    BhimInteger pi("31415926535897932"); //(17 str len) works with bpow 11

    if (static_cast<size_t>(bpow.to_int()) > pi.getDigitCount() - 1) {
        Log() << "Error : pow > pi digit count \n";
        return;
    }

    size_t digitsToRemove = pi.getDigitCount() - 1;

    BhimInteger tenToThePower = tenToThePower.powBhimInteger(10, digitsToRemove);

    BhimInteger divisor = bbase * tenToThePower;


    auto pi_mul_start = pi * result;


    pi_mul_start.setLastDigitsToZero(digitsToRemove);


    bool finished = false;

    BhimInteger quotient, r2w, digit;

    std::vector<int> digitsRev;

    while (!finished) {
        quotient = pi_mul_start / divisor;

        r2w = quotient * divisor;

        digit = pi_mul_start - r2w;
        digit = digit / tenToThePower;

        digitsRev.push_back(digit.to_int());

        pi_mul_start = pi_mul_start / bbase;

        pi_mul_start.setLastDigitsToZero(digitsToRemove);

        if (pi_mul_start.getDigitCount() <= digitsToRemove) {
            finished = true;
        }
    }

    QString res = "";
    for (int i = digitsRev.size() - 1; i >= 0; i--) {
        res += QString::number(digitsRev[i]) + ",";
    }

    Log() << "Digits: " << res;
}

QString mpzToString(mpz_t n)
{
    // Allocate a buffer large enough to hold the number
    // mpz_sizeinbase returns the size required to store n in base 10
    // Add 2 for the sign and null terminator
    size_t bufferSize = mpz_sizeinbase(n, 10) + 2;
    char *buffer = new char[bufferSize];

    // Convert mpz_t to char*
    mpz_get_str(buffer, 10, n);

    // Construct a std::string from char*
    QString str(buffer);

    // Clean up the buffer
    delete[] buffer;

    return str;
}

void calculator::gmpTrial1()
{
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n, 123456789); // Example number

    auto str = mpzToString(n);
    Log() << "Number: " << str;

    mpz_clear(n);
}

void calculator::gmpTrial2()
{
    /*
         mpz_t is the type defined for GMP integers.
         It is a pointer to the internals of the GMP integer data structure
       */
    mpz_t n;

    mpz_init(n);
    mpz_set_ui(n, 123456789); // Example number

    Log() << "n1 = " << mpzToString(n);

    /* 3. Add one to the number */

    mpz_add_ui(n, n, 1); /* n = n + 1 */

    /* 4. Print the result */

    Log() << "n + 1 = " << mpzToString(n);

    /* 5. Square n+1 */

    mpz_mul(n, n, n); /* n = n * n */

    Log() << "n+1 squared = " << mpzToString(n);

    /* 6. Clean up the mpz_t handles or else we will leak memory */
    mpz_clear(n);
}

void calculator::gmpTrial3()
{
    int base = 16;
    std::string decimal_str
        = "3.14159265358979323846264338327950288419716939937510582097494459230781640"
          "628620899862803482534211706798214808651328230664709384460955058223172535"
          "940812848111745028410270193852110555964462294895493038196442881097566593"
          "344612847564823378678316527120190914564856692346034861045432664821339360"
          "726024914127372458700660631558817488152092096282925409171536436789259036"
          "001133053054882046652138414695194151160943305727036575959195309218611738"
          "193261179310511854807446237996274956735188575272489122793818301194912983"
          "367336244065664308602139494639522473719070217986094370277053921717629317"
          "675238467481846766940513200056812714526356082778577134275778960917363717"
          "872146844090122495343014654958537105079227968925892354201995611212902196"
          "086403441815981362977477130996051870721134999999837297804995105973173281"
          "609631859502445945534690830264252230825334468503526193118817101000313783"
          "875288658753320838142061717766914730359825349042875546873115956286388235"
          "37875937519577818577805321712268066130019278766111959092164201989";

    // Set a very high precision for the floating-point numbers
    //const int precision = 10000000; // 10 million bits, adjust as needed

    //1 million bits is 250k digits. so you should adjust the digits based on the base and input length
    //if you have input length 1000 chars, base = 16, you should produce 1000 * 10/16 = 625 digits? approx? this is just a guess currently

    double dBase = static_cast<double>(base);

    double targetCharCount = (10.0 / dBase) * static_cast<double>(decimal_str.length());

    int targetPrecisionD = static_cast<int>(targetCharCount) * 4;

    //const int precision = 1000000; // 10 million bits, adjust as needed
    const int precision = targetPrecisionD;

    Log() << "precision = " << precision;

    mpf_set_default_prec(precision);

    mpf_t number, fractional_part, base_mpf, integer_part;
    mpf_inits(number, fractional_part, base_mpf, integer_part, nullptr);

    // Set the number and the base
    mpf_set_str(number, decimal_str.c_str(), 10);
    mpf_set_ui(base_mpf, base);

    QString hexString = "";

    // Convert the number
    while (mpf_cmp_ui(number, 0) > 0) {
        // Multiply the number by the base and separate integer and fractional parts
        mpf_mul(number, number, base_mpf);
        mpf_floor(integer_part, number);
        mpf_sub(fractional_part, number, integer_part);

        // Extract the next digit
        unsigned long int digit = mpf_get_ui(integer_part);

        // Output the digit
        //Log() << digit << ",";

        if (digit <= 15) {
            char c = decimalToHex(digit);
            hexString += c;
        }

        // Prepare for next iteration
        mpf_set(number, fractional_part);
    }

    Log() << "trial3 finished";

    Log() << "output = " << hexString;

    // Clear all the variables
    mpf_clears(number, fractional_part, base_mpf, integer_part, nullptr);
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

    while (!finished) {
        for (size_t i = 0; i < remainders.size(); i++) {
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
