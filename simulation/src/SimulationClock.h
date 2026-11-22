#pragma once

class SimulationClock
{
public:
    explicit SimulationClock(double dtSeconds);

    void tick();
    double dt() const;
    long long tickCount() const;
    double simTimeSeconds() const;

private:
    double dtSeconds_;
    long long tickCount_;
};