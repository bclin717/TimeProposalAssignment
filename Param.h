//
// Created by kevin on 2018/8/13.
//

#ifndef MTVRPTWSC_PARAM_H
#define MTVRPTWSC_PARAM_H

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>

#include "Customer.h"
#include "Chromosome.h"
#include "TimeWindow.h"

extern int NumberOfDeterministicCustomers;

static const int NumberOfChromosome = 10;
static const unsigned int NumberOfGeneration = 100;

const int T = 3;
static const int Alpha = 1;
static const int Beta = 160;
const int bBar = 160;

const int NumberOfTimeWindowCase = 12;
const int NumberOfTimeWindowSaleCase = 7;

extern std::vector<int> DefaultTimeWindow;
extern std::vector<std::vector<int>> saleDemand;
extern std::vector<std::vector<int>> minimumCostForAssigningCustomer;

#endif //MTVRPTWSC_PARAM_H
