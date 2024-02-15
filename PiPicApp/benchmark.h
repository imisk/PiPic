#ifndef BENCHMARK_H
#define BENCHMARK_H

// Benchmark tests to decide which bigint libraries are best

class inputDataManager;
class calculator;

class benchmark
{
public:
    benchmark(inputDataManager *nInputDataManager, calculator *nCalc);

    void accuracyTrialInputLength();
    void test();

    void accuracyTrialPrec();

    void accuracyTrialPrecMultiple();

private:
    inputDataManager *inputDataMngr;
    calculator *calc;
};

#endif  // BENCHMARK_H
