//
// Created by kevin on 2018/10/12.
//

#include "Param.h"

TimeWindow::TimeWindow() {
    _case = -1;
    _lowerBound = 0;
    _upperBound = 1440;
}

TimeWindow::TimeWindow(int c) {
    setTimeWindowCase(c);
}

TimeWindow::TimeWindow(const TimeWindow &_t) {
    _case = _t._case;
    _lowerBound = _t._lowerBound;
    _upperBound = _t._upperBound;
}

void TimeWindow::setTimeWindowCase(int c) {
    _case = c;
    _lowerBound = c*60 - 60;
    _upperBound = _lowerBound + 60;
}

int TimeWindow::getLowerBound() { return _lowerBound; }

void TimeWindow::setLowerBound(int lb) { _lowerBound = lb; }

int TimeWindow::getUpperBound() { return _upperBound; }

void TimeWindow::setUpperBound(int ub) { _upperBound = ub; }

int TimeWindow::getCase() { return _case; }
