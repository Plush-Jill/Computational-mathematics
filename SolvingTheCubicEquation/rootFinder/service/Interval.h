//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_INTERVAL_H
#define SOLVINGTHECUBICEQUATION_INTERVAL_H
#include "Side.h"
#include "../../Equation/Equation.h"
#include <string>


class Interval {
private:
    double begin;
    double end;
    void setBegin(double value);
    void setEnd(double value);
public:
    std::string toString();
    bool isContainsRoot(Equation equation, double epsilon);
    double getMiddle() const;
    Interval(double begin, double end);
    double getBegin() const;
    double getEnd() const;
    void expandInterval(Side side, double value);

};


#endif //SOLVINGTHECUBICEQUATION_INTERVAL_H
