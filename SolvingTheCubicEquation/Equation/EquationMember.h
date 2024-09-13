//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_EQUATIONMEMBER_H
#define SOLVINGTHECUBICEQUATION_EQUATIONMEMBER_H
#include <string>

class EquationMember {
private:
    double scalar;
    int variableDegree;


    void setVariableDegree(int newDegree);
    void setScalar(double newScalar);
public:
    std::string toString() const;
    EquationMember(double scalar, int variableDegree);
    void differentiate();
    double getScalar() const;
    int getVariableDegree() const;

    double calculate(double variableValue) const;
};


#endif //SOLVINGTHECUBICEQUATION_EQUATIONMEMBER_H
