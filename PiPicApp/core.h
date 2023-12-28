#ifndef CORE_H
#define CORE_H

#include "benchmark.h"
#include "calculator.h"
#include <inputDataManager.h>
#include <memory>
class core {
 public:
  core();

  void benchmark_test();

  void trial();

 private:
  benchmark bench;

  std::unique_ptr<calculator> calc;
  std::unique_ptr<inputDataManager> inputDataMngr;
};

#endif  // CORE_H
