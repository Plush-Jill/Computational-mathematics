//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_EQUATION_H
#define SOLVINGTHECUBICEQUATION_EQUATION_H
#include <vector>
#include "EquationMember.h"
#include "../rootFinder/service/Interval.h"

class Equation {
private:
    std::vector<EquationMember> nonZeroDegreeMembers;
    double zeroDegreeMember;
public:
    [[nodiscard]] bool isHasRootInInterval(Interval interval) const;
    double getScalarByDegree(int degree);
    double getDiscriminant();
    int getMaxDegree();
    void differentiate();
    Equation getDifferentiated();
    Equation(std::vector<double> scalars);
    Equation(double mainScalar, double a, double b, double c);
    Equation(Equation const &equation);
    [[nodiscard]] double calculate(double variableValue) const;
    std::string toString();

};


#endif //SOLVINGTHECUBICEQUATION_EQUATION_H
