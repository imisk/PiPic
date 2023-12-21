#include "core.h"
#include <iostream>
#include "logger.h"

core::core() {

    calc = std::make_unique<calculator>();

}

void core::benchmark_test() {

  Log() << "log message from benchmark_test";

}

void core::trial()
{
  //auto m = calc->getDigitDecimals(399);

  //calc->accuracyTrial2b();

  calc->gmpTrial3();
}

