//
// Created by bocka on 10.09.2024.
//

#include "EquationRoot.h"

double EquationRoot::getValue() const {
    return value;
}

int EquationRoot::getDegree() const {
    return degree;
}

void EquationRoot::setDegree(int degree) {
    this->degree = degree;
}

EquationRoot::EquationRoot(double value, int degree) {
    this->value = value;
    this->degree = degree;
}

void EquationRoot::incrementDegree() {
    ++this->degree;
}

std::string EquationRoot::toString() {
    std::string line = "[ROOT: " + std::to_string(this->value) + " degree: " + std::to_string(this->degree) + "]";
    return line;
}

EquationRoot::EquationRoot(double value) : EquationRoot(value, 1){
}
