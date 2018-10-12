//
// Created by kevin on 2018/10/12.
//

#include "Param.h"

Chromosome::Chromosome() {
    _fitnewssValue = 0;
    _wheelProbability = 0;

    for(unsigned int i = 0; i < NumberOfDeterministicCustomers; i++) {
        _customers.emplace_back(i);
    }

    for(unsigned int i = 1; i < _customers.size(); i++) {
        int j = static_cast<int>((rand() % (_customers.size() - 1)) + 1);
        Customer temp = _customers.at(i);
        _customers.at(i) = _customers.at(j);
        _customers.at(j) = temp;
    }

    _fitnewssValue = calculateFitnessValue();
}

Chromosome::Chromosome(std::vector<Customer> &c) {
    _fitnewssValue = 0;
    _wheelProbability = 0;
    _customers.assign(c.begin(), c.end());
    _fitnewssValue = calculateFitnessValue();
}

float Chromosome::calculateFitnessValue() {
//    Car car[NumberOfVehicle];
    float COST = 0;
    float TW = 0;
    int LOAD = 0;
    int carCount = 0;
    int nowCustomer, preCustomer;
//    car[carCount].route.push_back(0);
//    for(unsigned int i = 1; i < _customers.size(); i++) {
//        LOAD += _customers.at(i).getDemandQuantity();
//
//        if(_customers.at(i).getID() >= NumberOfDeterministicCustomers) nowCustomer = _customers.at(i).getID() - 15;
//        else nowCustomer = _customers.at(i).getID();
//
//        if(_customers.at(i-1).getID() >= NumberOfDeterministicCustomers) preCustomer = _customers.at(i-1).getID() - 15;
//        else preCustomer = _customers.at(i-1).getID();
//
//        if(LOAD > CapacityOfVehicle) {
//            COST += costMatrix[nowCustomer][0];
//            car[++carCount].route.push_back(0);
//            i--;
//            LOAD = 0;
//            continue;
//        } else {
//            TW = COST > _customers.at(i).getTimeWindow().getLowerBound() ? COST : _customers.at(i).getTimeWindow().getLowerBound();
//            COST += costMatrix[preCustomer][nowCustomer] + _customers.at(i).getServiceTime();
//            if (TW > _customers.at(i).getTimeWindow().getUpperBound())
//                COST += penalty(TW, _customers.at(i).getTimeWindow().getUpperBound());
//        }
//    }
    _fitnewssValue = COST;
    return COST;
}