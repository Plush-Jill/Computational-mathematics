//
// Created by bocka on 10.09.2024.
//

#ifndef SOLVINGTHECUBICEQUATION_EQUATIONROOT_H
#define SOLVINGTHECUBICEQUATION_EQUATIONROOT_H
#include <string>

class EquationRoot {
public:
    explicit EquationRoot(double value, int degree);
    explicit EquationRoot(double value);
    double getValue() const;
    int getDegree() const;
    void setDegree(int degree);
    void incrementDegree();
    std::string toString();
private:
    double value;
    int degree;
};


#endif //SOLVINGTHECUBICEQUATION_EQUATIONROOT_H
