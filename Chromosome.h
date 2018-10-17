//
// Created by kevin on 2018/10/12.
//

#include "Customer.h"

#ifndef TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
#define TIMEPROPOSALASSIGNMENT_CHROMOSOME_H

class Chromosome{
public:
    static bool cmp(const Chromosome &c1, const Chromosome &c2);
    Chromosome(bool random);
    Chromosome(std::vector<TimeWindow> &c);
    std::vector<TimeWindow> _timeWindows;

    float calculateFitnessValue();
    void random();


    void getTimeWindowCases();
    void getNumberOfTimeWindows();

    void setWheelProbability(double p);

    double getWheelProbability();

    bool isExists(int cID);

private:
    std::vector<int> numberOfTimeWindows;
    float _fitnewssValue;
    double _wheelProbability;

};

#endif //TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
