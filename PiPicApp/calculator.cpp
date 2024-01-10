#include "calculator.h"
#include <QString>
#include "../../gmp_build/gmp.h"
#include "logger.h"
#include "utility.h"
#include <set>
#include <vector>

calculator::calculator() {}

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
          "940812848111745028410270193852110555964462294895493038196442881097566593";

    // Set a very high precision for the floating-point numbers
    //const int precision = 10000000; // 10 million bits, adjust as needed

    //1 million bits is 250k digits. so you should adjust the digits based on the base and input length
    //if you have input length 1000 chars, base = 16, you should produce 1000 * 10/16 = 625 digits? approx? this is just a guess currently

    double dBase = static_cast<double>(base);

    double targetCharCount = (10.0 / dBase) * static_cast<double>(decimal_str.length());

    int targetPrecisionD = static_cast<int>(targetCharCount) * 4;

    //const int precision = 1000000; // 10 million bits, adjust as needed
    //const int precision = targetPrecisionD;
    const int precision = 100000000;

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
    //mpf_clears(number, fractional_part, base_mpf, integer_part, nullptr);
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

std::vector<unsigned long int> calculator::convertNumberToBase(std::string &inputNumber,
                                                               int base,
                                                               size_t maxDigits)
{
    const int precision = 20000000;

    std::vector<unsigned long int> ret;

    mpf_set_default_prec(precision);

    mpf_t number, fractional_part, base_mpf, integer_part;
    mpf_inits(number, fractional_part, base_mpf, integer_part, nullptr);

    // Set the number and the base
    mpf_set_str(number, inputNumber.c_str(), 10);
    mpf_set_ui(base_mpf, base);

    bool finished = false;

    // Convert the number
    while (finished != true) {
        // Multiply the number by the base and separate integer and fractional parts
        mpf_mul(number, number, base_mpf);
        mpf_floor(integer_part, number);
        mpf_sub(fractional_part, number, integer_part);

        // Extract the next digit
        unsigned long int digit = mpf_get_ui(integer_part);

        ret.push_back(digit);

        // Prepare for next iteration
        mpf_set(number, fractional_part);

        if (mpf_cmp_ui(number, 0) > 0) {
            finished = false;
        } else {
            finished = true;
        }

        if (ret.size() >= maxDigits) {
            finished = true;
        }
    }

    return ret;
}
