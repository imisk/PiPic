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
