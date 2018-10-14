//
// Created by kevin on 2018/10/12.
//

#include "Param.h"
#include "Customer.h"


Customer::Customer(int id) {
    _id = id;
    timeWindow.setTimeWindowCase(0);
}

Customer::Customer(int id, int timeWindowCase) {
    _id = id;
    timeWindow.setTimeWindowCase(timeWindowCase);
}

Customer::Customer(const Customer &c) {
    _id = c._id;
    timeWindow = TimeWindow(c.timeWindow);
}

int Customer::getID() {
    return _id;
}

void Customer::setID(int id) {
    _id = id;
}

void Customer::setTimeWindowCase(int timeWindowCase) {
    timeWindow.setTimeWindowCase(timeWindowCase);
}
