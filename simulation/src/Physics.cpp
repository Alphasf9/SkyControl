#include "Physics.h"
#include <cMath>

static const double PI = 3.14159265358979323846;
static const double SECONDS_PER_HOUR = 3600.0;

void updatePosition(Aircraft& ac, double dtSeconds) {
    double dtHours    = dtSeconds / SECONDS_PER_HOUR;
    double distanceNm = ac.speedKnots * dtHours;
    double headingRad = ac.headingDeg * PI / 180.0;

    ac.x += distanceNm * std::sin(headingRad);
    ac.y += distanceNm * std::cos(headingRad);
}

double normalizeHeading(double deg)
{
    double h = std::fmod(deg, 360.0);
    if (h < 0.0)
        h += 360.0;
    return h;
}

double shortestTurn(double fromDeg, double toDeg)
{
    double diff = std::fmod(toDeg - fromDeg, 360.0);
    if (diff > 180.0)
        diff -= 360.0;
    if (diff <= -180.0)
        diff += 360.0;
    return diff;
}

void updateHeading(Aircraft &ac, double dtSeconds)
{
    double diff = shortestTurn(ac.headingDeg, ac.targetHeadingDeg);
    double maxStep = ac.turnRateDegPerSec * dtSeconds;

    if (std::fabs(diff) <= maxStep)
    {
        ac.headingDeg = ac.targetHeadingDeg; // close enough: arrive exactly
    }
    else
    {
        ac.headingDeg += (diff > 0.0 ? maxStep : -maxStep);
    }
    ac.headingDeg = normalizeHeading(ac.headingDeg);
}