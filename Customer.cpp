//
// Created by kevin on 2018/10/12.
//

#include "Param.h"
#include "Customer.h"


Customer::Customer(int id) {
    id = id;
}

Customer::Customer(int id, int timeWindowCase) {
    id = id;
    timeWindow.setTimeWindowCase(timeWindowCase);
}

Customer::Customer(const Customer &c) {
    id = c.id;
    timeWindow = TimeWindow(c.timeWindow);
}

int Customer::getID() {
    return id;
}

void Customer::setID(int id) {
    id = id;
}

void Customer::setTimeWindowCase(int timeWindowCase) {
    timeWindow.setTimeWindowCase(timeWindowCase);
}
