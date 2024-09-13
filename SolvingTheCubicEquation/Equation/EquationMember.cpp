//
// Created by bocka on 10.09.2024.
//

#include "EquationMember.h"
#include <iostream>
#include <cmath>

double EquationMember::getScalar() const {
    return scalar;
}

void EquationMember::setScalar(double newScalar) {
    this->scalar = newScalar;
}

int EquationMember::getVariableDegree() const {
    return variableDegree;
}

void EquationMember::differentiate() {
    setScalar(getScalar() * getVariableDegree());
    setVariableDegree(getVariableDegree() - 1);
}

EquationMember::EquationMember(double scalar,  int variableDegree) {
    this->scalar = scalar;
    this->variableDegree = variableDegree;
}

void EquationMember::setVariableDegree(int newDegree) {
    this->variableDegree = newDegree;
}

std::string EquationMember::toString() const {
    if (getScalar() == 0) {
        return "";
    }
    std::string line = std::to_string(scalar) + 'x';
    if (getVariableDegree() != 1) {
        line += '^' + std::to_string(variableDegree);
    }
    return line;
}

double EquationMember::calculate(double variableValue) const {
    return pow(variableValue, this->getVariableDegree()) * getScalar();
}
