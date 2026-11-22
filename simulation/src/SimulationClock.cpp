#include "SimulationClock.h"

SimulationClock::SimulationClock(double dtSeconds)
    : dtSeconds_(dtSeconds), tickCount_(0) {}

void SimulationClock::tick() {
    tickCount_++;
}

double SimulationClock::dt() const {
    return dtSeconds_;
}

long long SimulationClock::tickCount() const {
    return tickCount_;
}

double SimulationClock::simTimeSeconds() const {
    return tickCount_ * dtSeconds_;
}