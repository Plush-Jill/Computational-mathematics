//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_CUBICEQUATIONROOTSFINDER_H
#define SOLVINGTHECUBICEQUATION_CUBICEQUATIONROOTSFINDER_H
#include "../Equation/Equation.h"
#include "service/EquationRoot.h"
#include "service/Interval.h"
#include "service/Side.h"


class CubicEquationRootsFinder {
private:
    double epsilon;
public:
    double getEpsilon() const;

private:
    double delta;
    std::vector<EquationRoot> findRootsOfSquareEquation(Equation equation);
    Interval findRootInterval(const Equation& equation, Side rootSide, Interval startInterval) const;
    Interval findRootInterval(const Equation& equation, Side rootSide);
    EquationRoot findRootInInterval(Equation equation, Interval interval) const;
    int checkRootDegree(Equation equation, EquationRoot root);

public:
    std::vector<EquationRoot> findRoots(Equation equation);
    CubicEquationRootsFinder(double epsilon, double delta);
    std::string getDiscriminantInfo(Equation equation);
    void setEpsilon(double epsilon);

    void setDelta(double delta);
};


#endif //SOLVINGTHECUBICEQUATION_CUBICEQUATIONROOTSFINDER_H
