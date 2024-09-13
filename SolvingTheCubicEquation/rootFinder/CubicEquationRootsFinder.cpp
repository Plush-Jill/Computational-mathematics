//
// Created by bocka on 10.09.2024.
//

#include "CubicEquationRootsFinder.h"
#include "service/Interval.h"
#include <cmath>
#include <format>

std::vector<EquationRoot> CubicEquationRootsFinder::findRoots(Equation equation) {
    std::vector<EquationRoot> roots;
    Equation differedEquation = equation.getDifferentiated();
    double discriminant = differedEquation.getDiscriminant();
    if (discriminant <= 0){
        double calculatedInZero = equation.calculate(0);
        if (std::abs(calculatedInZero) < epsilon) {
            roots.emplace_back(EquationRoot(0, 1));
        } else if (calculatedInZero > epsilon) {
            Interval rootInterval = findRootInterval(equation, LEFT);
            roots.emplace_back(findRootInInterval(equation, rootInterval));
        } else if (calculatedInZero < epsilon){
            Interval rootInterval = findRootInterval(equation, RIGHT);
            roots.emplace_back(findRootInInterval(equation, rootInterval));
        }
    } else {
        std::vector<EquationRoot> squareEquationRoots = this->findRootsOfSquareEquation(differedEquation);
        double x1 = squareEquationRoots[0].getValue();
        double x2 = squareEquationRoots[1].getValue();
        if (x1 > x2) {
            double t = x1;
            x1 = x2;
            x2 = t;
        }

        double fx1 = equation.calculate(x1);
        double fx2 = equation.calculate(x2);

        if (fx1 > epsilon) {
            if (fx2 > epsilon) {
                Interval rootInterval = findRootInterval(equation, LEFT, Interval(x1 - 10, x1));
                roots.emplace_back(findRootInInterval(equation, rootInterval));
            } else if (std::abs(fx2) < epsilon) {
                Interval rootInterval = findRootInterval(equation, LEFT, Interval(x1 - 10, x1));

                roots.emplace_back(findRootInInterval(equation, rootInterval));
                roots.emplace_back(EquationRoot(x2, 2));
            } else if (fx2 < -epsilon) {
                Interval centerRootInterval = Interval(x1, x2);

                roots.emplace_back(findRootInInterval(equation, findRootInterval(equation, LEFT, Interval(x1 - 10, x1))));
                roots.emplace_back(findRootInInterval(equation, centerRootInterval));
                roots.emplace_back(findRootInInterval(equation, findRootInterval(equation, RIGHT, Interval(x2, x2 + 10))));
            }
        } else if (std::abs(fx1) < epsilon) {
            if (fx2 < -epsilon) {
                roots.emplace_back(EquationRoot(x1, 2));
                roots.emplace_back(findRootInInterval(equation, findRootInterval(equation, RIGHT, Interval(x2, x2 + 10))));
            } else if (std::abs(fx2) < epsilon) {
                roots.emplace_back(EquationRoot((x1 + x2) / 2));
            }
        } else if (fx1 < -epsilon) {
            if (fx2 < -epsilon) {
                roots.emplace_back(findRootInInterval(equation, findRootInterval(equation, RIGHT, Interval(x2, x2 + 10))));
            }
        }

    }

//    if (roots.size() == 1) {
//        roots[0].setDegree(checkRootDegree(equation, roots[0]));
//    }
    return roots;
}

Interval CubicEquationRootsFinder::findRootInterval(const Equation& equation, Side rootSide, Interval startInterval) const {
    int k = 0;
    while (1){
        if (startInterval.isContainsRoot(equation, epsilon)) {
            break;
        }
        startInterval.expandInterval(rootSide, delta);
        ++k;
    }
    return startInterval;
}

Interval CubicEquationRootsFinder::findRootInterval(const Equation& equation, Side rootSide) {
    if (rootSide == LEFT) {
        return findRootInterval(equation, rootSide, Interval(-10, 0));
    } else {
        return findRootInterval(equation, rootSide, Interval(0, 10));
    }
}

EquationRoot CubicEquationRootsFinder::findRootInInterval(Equation equation, Interval interval) const {
    while (std::abs(equation.calculate(interval.getMiddle())) >= epsilon){
        Interval leftHalf = Interval(interval.getBegin(), interval.getMiddle());
        if (leftHalf.isContainsRoot(equation, epsilon)) {
            interval = leftHalf;
        } else {
            interval = Interval(interval.getMiddle(), interval.getEnd());
        }
    }

    return EquationRoot(interval.getMiddle());
}

CubicEquationRootsFinder::CubicEquationRootsFinder(double epsilon, double delta) {
    this->epsilon = epsilon;
    this->delta = delta;
}

std::vector<EquationRoot> CubicEquationRootsFinder::findRootsOfSquareEquation(Equation equation) {
    double discriminant = equation.getDiscriminant();
    double a = equation.getScalarByDegree(2);
    double b = equation.getScalarByDegree(1);

    std::vector<EquationRoot> result;
    double fx1 = (-std::sqrt(discriminant) - b) / (2 * a);
    double fx2 = (std::sqrt(discriminant) - b) / (2 * a);

    result.emplace_back(fx1);
    result.emplace_back(fx2);

    return result;
}

void CubicEquationRootsFinder::setEpsilon(double epsilon) {
    CubicEquationRootsFinder::epsilon = epsilon;
}

void CubicEquationRootsFinder::setDelta(double delta) {
    CubicEquationRootsFinder::delta = delta;
}

std::string CubicEquationRootsFinder::getDiscriminantInfo(Equation equation) {
    double discriminant = equation.getDifferentiated().getDiscriminant();

    if (discriminant <= 0) {
        return std::format("[D <= 0, f(0) = {}]",equation.calculate(0));
    }

    std::vector<EquationRoot> squareRoots = findRootsOfSquareEquation(equation.getDifferentiated());

    double x1 = (squareRoots[0].getValue() < squareRoots[1].getValue()) ?
            squareRoots[0].getValue() : squareRoots[1].getValue();
    double x2 = (squareRoots[0].getValue() > squareRoots[1].getValue()) ?
                squareRoots[0].getValue() : squareRoots[1].getValue();
    double fx1 = equation.calculate(x1);
    double fx2 = equation.calculate(x2);

    std::string res = std::format("[D > 0, ", discriminant);

    if (fx1 > epsilon) {
        res += "f(x1) > e, ";
        if (fx2 > epsilon) {
            res += "f(x2) > e]";
        } else if (std::abs(fx2) < epsilon) {
            res += "|f(x2)| < e]";
        } else if (fx2 < -epsilon) {
            res += "f(x2) < -e]";
        }
    } else if (std::abs(fx1) < epsilon) {
        res += "f(x1) < e, ";
        if (fx2 < -epsilon) {
            res += "f(x2) < -e]";
        } else if (std::abs(fx2) < epsilon) {
            res += "|f(x2)| < e]";
        }
    } else if (fx1 < -epsilon) {
        res += "f(x1) < -e, ";
        if (fx2 < -epsilon) {
            res += "f(x2) < -e]";
        }
    }

    return res;
}

double CubicEquationRootsFinder::getEpsilon() const {
    return epsilon;
}

int CubicEquationRootsFinder::checkRootDegree(Equation equation, EquationRoot root) {
    int degree = 0;
    Equation sideEquation = equation;
    for (int i {}; i < 3; ++i) {
        if (sideEquation.calculate(root.getValue()) == 0) {
            ++degree;
        } else {
            break;
        }
        sideEquation.differentiate();
    }

    return degree;
}
