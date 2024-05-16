#ifndef CORE_H
#define CORE_H

#include "benchmark.h"
#include "calculator.h"
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

    MainWindow* mw;
    queueManager qm;
};

#endif  // CORE_H
