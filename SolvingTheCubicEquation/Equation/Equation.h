//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_EQUATION_H
#define SOLVINGTHECUBICEQUATION_EQUATION_H
#include <vector>
#include "EquationMember.h"

class Equation {
private:
    std::vector<EquationMember> nonZeroDegreeMembers;
    double zeroDegreeMember;
public:
    double getZeroDegreeMember() const;


public:
    double getScalarByDegree(int degree);
    double getDiscriminant();
    int getMaxDegree();
    void differentiate();
    Equation getDifferentiated();
    Equation(std::vector<double> scalars);
    Equation(double mainScalar, double a, double b, double c);
    Equation(Equation const &equation);
    void printEquation();
    double calculate(double variableValue);

    std::string toString();
};


#endif //SOLVINGTHECUBICEQUATION_EQUATION_H
