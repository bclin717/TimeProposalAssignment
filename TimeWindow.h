//
// Created by kevin on 2018/10/12.
//

#ifndef TIMEPROPOSALASSIGNMENT_TIMEWINDOW_H
#define TIMEPROPOSALASSIGNMENT_TIMEWINDOW_H

class TimeWindow {
public:
    TimeWindow();

    TimeWindow(const TimeWindow &t);

    int getLowerBound();

    void setLowerBound(int lb);

    int getUpperBound();

    void setUpperBound(int ub);

    void setTimeWindowCase(int c);

private:
    int _lowerBound;
    int _upperBound;
};

#endif //TIMEPROPOSALASSIGNMENT_TIMEWINDOW_H
