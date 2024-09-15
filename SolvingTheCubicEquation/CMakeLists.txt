cmake_minimum_required(VERSION 3.23)
project(SolvingTheCubicEquation)

set(CMAKE_CXX_STANDARD 23)

add_executable(SolvingTheCubicEquation
        main.cpp
        Equation/Equation.cpp Equation/Equation.h
        Equation/EquationMember.cpp Equation/EquationMember.h
        rootFinder/CubicEquationRootsFinder.cpp rootFinder/CubicEquationRootsFinder.h
        rootFinder/service/EquationRoot.cpp rootFinder/service/EquationRoot.h
        rootFinder/service/Interval.cpp rootFinder/service/Interval.h
        rootFinder/service/Side.h
)
