//
// Created by kevin on 2018/10/12.
//

#include "Customer.h"

#ifndef TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
#define TIMEPROPOSALASSIGNMENT_CHROMOSOME_H

class Chromosome{
public:
    Chromosome();
    Chromosome(std::vector<Customer> &c);
    std::vector<Customer> _customers;

    float calculateFitnessValue();

private:
    float _fitnewssValue;
    double _wheelProbability;

};

#endif //TIMEPROPOSALASSIGNMENT_CHROMOSOME_H
