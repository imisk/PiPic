#include "core.h"
#include <iostream>
#include "logger.h"

core::core() {}

void core::benchmark_test() {

  Log() << "log message from benchmark_test";

  // bench.test1();
  // bench.test2();

  bench.dec6_test(); //calculate pi to 150 digits in another base

  // bench.test3();

  //bench.test4();

   //bench.testRW();
  //bench.dec300_test();
}
