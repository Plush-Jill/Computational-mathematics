#include <iostream>
#include "Equation/Equation.h"
#include "rootFinder/service/EquationRoot.h"
#include "rootFinder/CubicEquationRootsFinder.h"
#include <vector>
#include <fstream>
#include <format>

int main() {
    CubicEquationRootsFinder rootsFinder = CubicEquationRootsFinder(10e-5, 0);
    std::ifstream testDataFile = std::ifstream("CubicEquationTestOrdered.txt");
    std::vector<double> epsilonSet = {0.0000001, 0.0001, 0.1, 1};


    if (testDataFile.is_open()) {
        double a, b, c, delta;
        for (int i{}; i < 17; ++i) {
            testDataFile >> a >> b >> c >> delta;
            std::cout << std::format("{} {} {}    \n", a, b, c);
            rootsFinder.setDelta(delta);


            Equation equation = Equation(1.0, a, b, c);
            std::cout << std::format("{} (delta = {}, epsilon = {})\n", equation.toString(), delta,
                                     rootsFinder.getEpsilon());

            std::vector<EquationRoot> roots = rootsFinder.findRoots(equation);
            for (EquationRoot root: roots) {
                std::cout << std::format("[{} f(x) = {}]\n", root.toString(), equation.calculate(root.getValue()));
            }
            std::cout << std::fixed << rootsFinder.getDiscriminantInfo(equation) << std::endl;
            std::cout << "\n";
        }

        for (int i{}; i < 2; ++i) {
            testDataFile >> a >> b >> c >> delta;
            rootsFinder.setDelta(delta);


            for (int j{}; j < epsilonSet.size(); ++j) {
                rootsFinder.setEpsilon(epsilonSet[j]);


                Equation equation = Equation(1.0, a, b, c);
                std::cout << std::format("{} {} {}    \n", a, b, c);
                std::cout << std::format("{} (delta = {}, epsilon = {})\n", equation.toString(), delta,
                                         rootsFinder.getEpsilon());

                std::vector<EquationRoot> roots = rootsFinder.findRoots(equation);
                for (EquationRoot root: roots) {
                    std::cout << std::format("[{} f(x) = {}]\n", root.toString(), equation.calculate(root.getValue()));
                }
                std::cout << std::fixed << rootsFinder.getDiscriminantInfo(equation) << std::endl;
                std::cout << "\n";
            }
        }

        testDataFile.close();
    }



    return 0;
}
