//
// Created by kevin on 2018/10/12.
//

#ifndef TIMEPROPOSALASSIGNMENT_CUSTOMER_H
#define TIMEPROPOSALASSIGNMENT_CUSTOMER_H
#include "TimeWindow.h"

class Customer {
public:
    Customer(const Customer &c);
    Customer(int id);
    Customer(int id, int timeWindowCase);

    void setID(int id);
    int getID();

    void setTimeWindowCase(int timeWindowCase);
    TimeWindow getTimeWindow();
private:
    int _id;
    TimeWindow timeWindow;

};

#endif //TIMEPROPOSALASSIGNMENT_CUSTOMER_H
