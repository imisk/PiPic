#include "benchmark.h"
#include <iostream>

#include <chrono>
#include "BhimInteger.h"
#include "bigint.h"

benchmark::benchmark() {}

void benchmark::test1() {
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

void benchmark::test2() {
  std::cout << "test 2 runs \n";

  auto start = std::chrono::high_resolution_clock::now();

  int pow = 5000;

  BhimInteger base("4");

  BhimInteger result("4");

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
  std::cout << "Time taken by test2(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';
}

void benchmark::dec6_test() {
  size_t base = 16;
  std::string pow = "6";

  std::string sbase = "16";  // todo: convert from int base
  BhimInteger bbase(sbase);

  BhimInteger result;

  result = result.powBhimInteger(sbase, pow);

  // todo test loop this vs powBhimInteger

  //  for (int curPow = 0; curPow < pow - 1; ++curPow) {
  //    if (curPow % 100 == 0) {
  //      std::cout << "cp = " << curPow << '\n';
  //    }
  //  }

  std::cout << "start result = " << result << '\n';

  BhimInteger pi("31415926535897932");

  auto pi_mul_start = pi * result;

  std::cout << "pi_mul_start = " << pi_mul_start << '\n';

  size_t curLength = pi_mul_start.getDigitCount();

  size_t remainingDigits = curLength - base;

  pi_mul_start.removeDigitsAfterIdx(remainingDigits);

  std::cout << "pi_mul_start 2 = " << pi_mul_start << '\n';

  BhimInteger quotient, r2w, digit;

  //----

  bool finished = false;
  while (!finished) {
    quotient = pi_mul_start / bbase;
    // cout << "r2 = " << quotient << '\n';
    r2w = quotient * bbase;
    // cout << "r2w = " << r2w << '\n';
    digit = pi_mul_start - r2w;
    cout << "digit *********** = " << digit << '\n';
    pi_mul_start = quotient;

    if (quotient == 0) {
      finished = true;
    }
  }

  ///
}

void benchmark::test3() {
  size_t base = 4;
  std::string pow = "5000";

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
