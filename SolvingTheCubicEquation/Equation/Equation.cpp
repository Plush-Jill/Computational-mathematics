//
// Created by bocka on 10.09.2024.
//

#include <iostream>
#include "Equation.h"
#include "EquationMember.h"

Equation::Equation(std::vector<double> scalars) {
    for (int i {}; i < scalars.size() - 1; ++i){
        this->nonZeroDegreeMembers.emplace_back(scalars.at(i), scalars.size() - i - 1);
    }
    this->zeroDegreeMember = scalars[scalars.size() - 1];

}

std::string Equation::toString() {
    std::string result;
    for (int i {}; i < nonZeroDegreeMembers.size(); ++i) {
        std::string line = nonZeroDegreeMembers.at(i).toString();
        if (line.empty()){
            continue;
        }
        result += nonZeroDegreeMembers.at(i).toString() + " + ";
    }

    result += std::to_string(zeroDegreeMember) + " = 0";
    return result;
}

Equation::Equation(double mainScalar, double a, double b, double c) {
    this->nonZeroDegreeMembers.emplace_back(EquationMember(mainScalar, 3));
    this->nonZeroDegreeMembers.emplace_back(EquationMember(a, 2));
    this->nonZeroDegreeMembers.emplace_back(EquationMember(b, 1));
    this->zeroDegreeMember = c;
}

void Equation::differentiate() {
    for (int i {}; i < nonZeroDegreeMembers.size() - 1; ++i){
        nonZeroDegreeMembers.at(i).differentiate();
    }
    zeroDegreeMember = nonZeroDegreeMembers.at(nonZeroDegreeMembers.size() - 1).getScalar();
    nonZeroDegreeMembers.pop_back();
}

int Equation::getMaxDegree() {
    return nonZeroDegreeMembers.at(0).getVariableDegree();
}

double Equation::getDiscriminant() {
    if (getMaxDegree() != 2){
        throw std::exception();
    }
    double a = getScalarByDegree(2);
    double b = getScalarByDegree(1);
    double c = getScalarByDegree(0);
    return (b * b - 4 * a * c);
}

Equation Equation::getDifferentiated() {
    Equation sideEquation = Equation(*this);
    sideEquation.differentiate();
    return sideEquation;
}

Equation::Equation(const Equation &equation) {
    this->nonZeroDegreeMembers = equation.nonZeroDegreeMembers;
    this->zeroDegreeMember = equation.zeroDegreeMember;
}

double Equation::calculate(double variableValue) const {
    double sum {};
    for (EquationMember x : nonZeroDegreeMembers) {
        sum += x.calculate(variableValue);
    }
    sum += zeroDegreeMember;
    return sum;
}

double Equation::getScalarByDegree(int degree) {
    return (degree == 0) ? zeroDegreeMember : nonZeroDegreeMembers[nonZeroDegreeMembers.size() - degree].getScalar();
}

bool Equation::isHasRootInInterval(Interval interval) const {
    double fa = this->calculate(interval.getBegin());
    double fb = this->calculate(interval.getEnd());
    bool result = (fa < 0 && fb > 0) || (fa > 0 && fb < 0);
    return result;
}
