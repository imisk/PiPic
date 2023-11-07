#include "benchmark.h"
#include <iostream>

#include <chrono>
#include "bhimInteger.h"
#include "bigInt.h"
#include "dataManager.h"
#include "utility.h"
#include "logger.h"

benchmark::benchmark() {}

void benchmark::test1() {
  //speed test
  std::cout << "test 1 runs \n";

  auto start = std::chrono::high_resolution_clock::now();

  int pow = 5000;

  bigint base("4");  // big integer initialization
                     // with String

  bigint result("4");

  for (int curPow = 0; curPow < pow; ++curPow) {
    result *= base;
    //    if (curPow % 100 == 0) {
    //      std::cout << "cp = " << curPow << '\n';
    //    }
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by test1(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';

}

void benchmark::test2()
{
  std::cout << "test 2 runs \n";

  auto start = std::chrono::high_resolution_clock::now();

  int pow = 20000;

  BhimInteger base("4");

  BhimInteger result("4");

  for (int curPow = 0; curPow < pow - 1; ++curPow) {
    result *= base;
    //    if (curPow % 100 == 0) {
    //      std::cout << "cp = " << curPow << '\n';
    //    }
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by test2(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';

}

void benchmark::dec6_test() {
  //this function calculates Pi to pow digits in sbase base.
  // pow is the digit count we will be calculating up to

  BhimInteger bpow("1000");

  std::string sbase = "16";
  BhimInteger bbase(sbase);

  BhimInteger result;

  result = result.powBhimInteger(sbase, bpow);

  // this loop is slightly faster than powBhimInteger, we should use it

  //  for (int curPow = 0; curPow < pow - 1; ++curPow) {
  //    if (curPow % 100 == 0) {
  //      std::cout << "cp = " << curPow << '\n';
  //    }
  //  }

  Log() << "start result = " << result.toQString();

  BhimInteger pi(
      "314159265358979323846264338327950288419716939937510582097494459230781640"
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
      "37875937519577818577805321712268066130019278766111959092164201989");

  if (static_cast<size_t>(bpow.to_int()) > pi.getDigitCount() - 1) {
    Log() << "Error : pow > pi digit count \n";
    return;
  }

  Log() << "Input pi digit count = " << pi.getDigitCount();

  size_t digitsToRemove = pi.getDigitCount() - 1;

  auto pi_mul_start = pi * result;

  Log() << "pi_mul_start = " << QString(pi_mul_start.toString().c_str()) << '\n';

  size_t curLength = pi_mul_start.getDigitCount();

  size_t remainingDigits = curLength - digitsToRemove;

  pi_mul_start.removeDigitsAfterIdx(remainingDigits);

  Log() << "pi_mul_start 2 = " << QString(pi_mul_start.toString().c_str()) << '\n';

  BhimInteger quotient, r2w, digit;

  //----

  bool finished = false;

  std::cout << "\n\nDIGITS OUTPUT: \n";

  std::string resultReversed = "";

  while (!finished) {
    quotient = pi_mul_start / bbase;
    // cout << "r2 = " << quotient << '\n';
    r2w = quotient * bbase;
    // cout << "r2w = " << r2w << '\n';
    digit = pi_mul_start - r2w;
    // cout << "digit *********** = " << digit << '\n';

    char digitChar = decimalToHex(digit.to_int());

    resultReversed.push_back(digitChar);

    pi_mul_start = quotient;

    if (quotient == 0) {
      finished = true;
    }
  }

  Log() << "reversed = " << QString(resultReversed.c_str()) << "\n\n";
  reverseString(resultReversed);
  Log() << "normal = " << QString(resultReversed.c_str()) << '\n';

  std::cout << '\n';

  ///
}

void benchmark::test3() {
  //speed test
  std::string pow = "20000";

  std::string sbase = "4";  // todo: convert from int base
  BhimInteger bbase(sbase);

  BhimInteger result;

  auto start = std::chrono::high_resolution_clock::now();

  result = result.powBhimInteger(sbase, pow);

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by test3(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';
}

void benchmark::test3b()
{
  //speed test
  std::string pow = "30000";

  std::string sbase = "4";  // todo: convert from int base
  BhimInteger bbase(sbase);

  BhimInteger result;

  auto start = std::chrono::high_resolution_clock::now();

  result = result.powBhimInteger(sbase, pow);

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by test3b(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';

}

void benchmark::testRW() {

  Log() << "testRW";

  BhimInteger pi(
      "314159265358979323846264338327950288419716939937510582097494459230781640"
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
      "378759888888888888888888");

  datamanager dm;


  std::string fn = "test1.val";
  dm.Write_Value(fn, pi);

  BhimInteger pr;

  dm.Read_Value(fn, pr);

  Log() << "pr = " << pr.toQString() << '\n';
}

void benchmark::test4() {
  std::cout << "Testing cout output after update \n";
  //  LogMessage();
}

void benchmark::dec300_test()
{
  //this function calculates Pi to pow digits in sbase base.
  // pow is the digit count we will be calculating up to

  BhimInteger bpow("150");

  std::string sbase = "300";
  BhimInteger bbase(sbase);

  BhimInteger result;

  result = result.powBhimInteger(sbase, bpow);

  Log() << "start result = " << result.toQString();

  BhimInteger pi(
      "314159265358979323846264338327950288419716939937510582097494459230781640"
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
      "37875937519577818577805321712268066130019278766111959092164201989");

  if (static_cast<size_t>(bpow.to_int()) > pi.getDigitCount() - 1) {
    Log() << "Error : pow > pi digit count \n";
    return;
  }

  size_t digitsToRemove = pi.getDigitCount() - 1;

  auto pi_mul_start = pi * result;

  Log() << "pi_mul_start = " << QString(pi_mul_start.toString().c_str()) << '\n';

  size_t curLength = pi_mul_start.getDigitCount();

  size_t remainingDigits = curLength - digitsToRemove;

  pi_mul_start.removeDigitsAfterIdx(remainingDigits);

  Log() << "pi_mul_start 2 = " << QString(pi_mul_start.toString().c_str()) << '\n';

  BhimInteger quotient, r2w, digit;

  //----

  bool finished = false;

  std::cout << "\n\nDIGITS OUTPUT: \n";

  std::vector<int> resultReversed;

  while (!finished) {
    quotient = pi_mul_start / bbase;
    // cout << "r2 = " << quotient << '\n';
    r2w = quotient * bbase;
    // cout << "r2w = " << r2w << '\n';
    digit = pi_mul_start - r2w;
    // cout << "digit *********** = " << digit << '\n';

    resultReversed.push_back(digit.to_int());

    pi_mul_start = quotient;

    if (quotient == 0)
    {
      finished = true;
    }
  }

  //Log() << "reversed = " << QString(resultReversed.c_str()) << "\n\n";
  //reverseString(resultReversed);
  //Log() << "normal = " << QString(resultReversed.c_str()) << '\n';

  QString qResult = "";

  for (std::size_t i = resultReversed.size(); i-- > 0; )
  {
    qResult += QString::number(resultReversed[i]);
    qResult += "_";
  }

  Log() << "qResult = " << qResult;

  Log() << "Digit count = " << resultReversed.size();
}
