#include "core.h"
#include "inputDataManager.h"
#include "logger.h"
#include <dataManager.h>

#include <mainWindow.h>
#include <queueManager.h>

core::core(MainWindow* nMw)
{
    mw = nMw;

    calc = std::make_unique<calculator>();
    inputDataMngr = std::make_unique<inputDataManager>();

    bench = std::make_unique<benchmark>(inputDataMngr.get(), calc.get());

    dataMngr = std::make_unique<dataManager>();

    QAction::connect(&qm, &queueManager::forwardDigitProgress, mw, &MainWindow::updateDigitProgress);
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

  //bench->test();

  //----------- main ones:

  qm.executeItem(dataMngr.get());

  //qm.createImageSeries();

  dataManager dm;
  //dm.findFinishedDigits();
  //dm.createABCLogs();

  std::vector<int> f;
  std::vector<int> r;

  dm.loadABCLogs(f, r);

  qDebug() << "fin size = " << f.size();
}
