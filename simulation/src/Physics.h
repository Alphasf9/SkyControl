#pragma once

#include "Aircraft.h"

void updatePosition(Aircraft &ac, double dtSeconds);

double normalizeHeading(double deg);
double shortestTurn(double fromDeg, double toDeg);
void updateHeading(Aircraft &ac, double dtSeconds);

double approach(double current, double target, double maxStep);
void updateSpeed(Aircraft &ac, double dtSeconds);