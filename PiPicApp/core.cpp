#include "core.h"
#include "inputDataManager.h"
#include "logger.h"
#include <iostream>
#include <queueManager.h>

core::core() {

    calc = std::make_unique<calculator>();
    inputDataMngr = std::make_unique<inputDataManager>();

    bench = std::make_unique<benchmark>(inputDataMngr.get(), calc.get());
}

void core::benchmark_test() {

  Log() << "log message from benchmark_test";

}

void core::trial()
{
  //auto m = calc->getDigitDecimals(399);

  //calc->accuracyTrial2b();

  //calc->gmpTrial3();

  //QString pi;
  //inputDataMngr->loadPiFromDisk1Million(20, pi);

  //std::string path = "10k/41.txt";
  //auto ints = inputDataMngr->loadKnownCalculation(path);

  //bench->accuracyTrialInputLength();

  //auto d = inputDataMngr->getInformationRatioMultiplier(12);

  //bench->accuracyTrialPrec();

  //bench->accuracyTrialPrecMultiple();

  //bench->saveLoadTrial();

  queueManager qm;

  qm.executeItem();
}
