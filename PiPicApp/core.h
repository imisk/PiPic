#ifndef CORE_H
#define CORE_H

#include "benchmark.h"
#include <memory>
#include "calculator.h"

class core {
 public:
  core();

  void benchmark_test();

  void trial();

 private:
  benchmark bench;

    std::unique_ptr<calculator> calc;
};

#endif  // CORE_H
