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
    if (curPow % 100 == 0) {
      std::cout << "cp = " << curPow << '\n';
    }
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by longFunc(): " << duration << " milliseconds"
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
    if (curPow % 100 == 0) {
      std::cout << "cp = " << curPow << '\n';
    }
  }

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  // Print the elapsed time in milliseconds
  std::cout << "Time taken by longFunc(): " << duration << " milliseconds"
            << std::endl;

  std::cout << "result = " << result << '\n';
}

void benchmark::dec6_test() {
  int decimals = 6;
  int base = 16;
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

  //----

  auto r2 = pi_mul_start / bbase;

  cout << "r2 = " << r2 << '\n';

  auto r2w = r2 * bbase;

  cout << "r2w = " << r2w << '\n';

  auto digit = pi_mul_start - r2w;

  cout << "digit = " << digit << '\n';
}
