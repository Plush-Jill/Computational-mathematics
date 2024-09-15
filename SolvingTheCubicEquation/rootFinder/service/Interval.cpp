//
// Created by bocka on 10.09.2024.
//

#include <format>
#include "Interval.h"

double Interval::getMiddle() const {
    return (end + begin) / 2;
}

Interval::Interval(double begin, double end) : begin(begin), end(end) {}

double Interval::getBegin() const {
    return begin;
}

double Interval::getEnd() const {
    return end;
}

void Interval::expandInterval(Side side, double value) {
    if (side == LEFT) {
        setBegin(getBegin() - value);
    } else if (side == RIGHT) {
        setEnd(getEnd() + value);
    }
}

void Interval::setBegin(double value) {
    this->begin = value;
}

void Interval::setEnd(double value) {
    this->end = value;
}

std::string Interval::toString() {
    return "[" + std::to_string(begin) + ", " + std::to_string(end) + "]";
}
