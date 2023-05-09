#include "core.h"
#include <iostream>

core::core() {}

void core::benchmark_test() {
  std::cout << "bt \n";

  bench.test1();
  bench.test2();
}
