#pragma once

#include<string>


struct Aircraft {
    std:: string id;
    std:: string flightNumber;

    double x;
    double y;
    double altitudeFt;

    double speedKnots;
    double headingDeg;

    double targetHeadingDeg;
    double turnRateDegPerSec;
};

