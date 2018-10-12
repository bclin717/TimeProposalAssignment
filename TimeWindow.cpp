    //
// Created by kevin on 2018/10/12.
//

#include "Param.h"

TimeWindow::TimeWindow() {
    _lowerBound = 0;
    _upperBound = 1440;
}

TimeWindow::TimeWindow(const TimeWindow &_t) {
    _lowerBound = _t._lowerBound;
    _upperBound = _t._upperBound;
}

void TimeWindow::setTimeWindowCase(int c) {
    _lowerBound = c*60 - 60;
    _upperBound = _lowerBound + 60;
}

int TimeWindow::getLowerBound() { return _lowerBound; }

void TimeWindow::setLowerBound(int lb) { _lowerBound = lb; }

int TimeWindow::getUpperBound() { return _upperBound; }

void TimeWindow::setUpperBound(int ub) { _upperBound = ub; }

