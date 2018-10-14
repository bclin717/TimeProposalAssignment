//
// Created by kevin on 2018/10/12.
//

#include "Customer.h"

#ifndef TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
#define TIMEPROPOSALASSIGNMENT_CHROMOSOME_H

class Chromosome{
public:
    Chromosome(bool random);
    Chromosome(std::vector<TimeWindow> &c);
    std::vector<TimeWindow> _timeWindows;

    float calculateFitnessValue();
    void random();
    void getTimeWindowCases();

private:
    float _fitnewssValue;
    double _wheelProbability;

};

#endif //TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
