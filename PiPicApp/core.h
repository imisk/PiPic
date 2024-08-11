#ifndef CORE_H
#define CORE_H

#include "benchmark.h"
#include "calculator.h"
#include <dataManager.h>
#include <inputDataManager.h>
#include <memory>

#include <queueManager.h>

class MainWindow;

class core {
public:
    core(MainWindow* nMw);

    void benchmark_test();

    void trial();

private:
    std::unique_ptr<benchmark> bench;

    std::unique_ptr<calculator> calc;
    std::unique_ptr<inputDataManager> inputDataMngr;
    std::unique_ptr<dataManager> dataMngr;

    MainWindow* mw;
    queueManager qm;
};

#endif  // CORE_H
