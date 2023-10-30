#include "core.h"
#include <iostream>
#include "logger.h"

core::core() {}

void core::benchmark_test() {
  std::cout << "bt \n";

  Log() << "log message from benchmark_test";

  // bench.test1();
  // bench.test2();

  // bench.dec6_test();

  // bench.test3();

  // bench.testRW();

  bench.test4();
}
