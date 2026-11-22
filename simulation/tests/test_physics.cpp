
#include <iostream>
#include <cmath>

#include "../src/Aircraft.h"
#include "../src/Physics.h"
#include "../src/Commands.h"

static int failures = 0;

// Compares two doubles. Passes if they differ by less than tol.
void expectNear(
    const char *name,
    double actual,
    double expected,
    double tol = 1e-6)
{
    if (std::fabs(actual - expected) < tol)
    {
        std::cout << "PASS  " << name << "\n";
    }
    else
    {
        std::cout << "FAIL  " << name
                  << "  expected " << expected
                  << " but got " << actual << "\n";

        failures++;
    }
}

Aircraft makeAircraft(
    double x,
    double y,
    double speedKnots,
    double headingDeg)
{
    Aircraft ac;

    ac.id = "TEST";
    ac.flightNumber = "TEST-1";
    ac.x = x;
    ac.y = y;
    ac.altitudeFt = 10000.0;
    ac.speedKnots = speedKnots;
    ac.headingDeg = headingDeg;

    // Initialize turning data
    ac.targetHeadingDeg = headingDeg;
    ac.turnRateDegPerSec = 3.0;

    return ac;
}

int main()
{
    // =========================================
    // TEST 1: EAST MOVEMENT
    // East at 120 kt for 30 minutes -> (60, 0)
    // =========================================

    Aircraft a = makeAircraft(0, 0, 120.0, 90.0);

    updatePosition(a, 1800.0);

    expectNear("east: x", a.x, 60.0);
    expectNear("east: y", a.y, 0.0);

    // =========================================
    // TEST 2: NORTH MOVEMENT
    // North at 200 kt for 60 seconds
    // =========================================

    Aircraft b = makeAircraft(-45, 0, 200.0, 0.0);

    updatePosition(b, 60.0);

    expectNear("north: x", b.x, -45.0);
    expectNear("north: y", b.y, 200.0 / 60.0);

    // =========================================
    // TEST 3: SOUTH MOVEMENT
    // South at 300 kt for 60 seconds
    // =========================================

    Aircraft c = makeAircraft(5, 20, 300.0, 180.0);

    updatePosition(c, 60.0);

    expectNear("south: x", c.x, 5.0);
    expectNear("south: y", c.y, 15.0);

    // =========================================
    // TEST 4: MULTIPLE TICKS VS ONE STEP
    // =========================================

    Aircraft d = makeAircraft(0, 0, 360.0, 45.0);

    for (int i = 0; i < 6; i++)
    {
        updatePosition(d, 10.0);
    }

    Aircraft e = makeAircraft(0, 0, 360.0, 45.0);

    updatePosition(e, 60.0);

    expectNear("ticks vs one step: x", d.x, e.x);
    expectNear("ticks vs one step: y", d.y, e.y);

    // =========================================
    // TEST 5: COMMAND VALIDATION
    // =========================================

    Aircraft cmd = makeAircraft(0, 0, 200.0, 45.0);

    // Initial target heading = 45
    // Current heading = 45

    CommandResult r1 = commandHeading(cmd, 90.0);

    expectNear(
        "command 90: target heading",
        cmd.targetHeadingDeg,
        90.0);

    expectNear(
        "command 90: current heading unchanged",
        cmd.headingDeg,
        45.0);

    // Invalid: heading is 360

    CommandResult r2 = commandHeading(cmd, 360.0);

    expectNear(
        "command 360: target unchanged",
        cmd.targetHeadingDeg,
        90.0);

    // Invalid: negative heading

    CommandResult r3 = commandHeading(cmd, -5.0);

    expectNear(
        "command -5: target unchanged",
        cmd.targetHeadingDeg,
        90.0);

    // Invalid: heading exceeds 360

    CommandResult r4 = commandHeading(cmd, 450.0);

    expectNear(
        "command 450: target unchanged",
        cmd.targetHeadingDeg,
        90.0);

    // Display command results

    std::cout << "\n--- COMMAND RESULTS ---\n";

    std::cout << "90:  " << toString(r1) << "\n";
    std::cout << "360: " << toString(r2) << "\n";
    std::cout << "-5:  " << toString(r3) << "\n";
    std::cout << "450: " << toString(r4) << "\n";

    // =========================================
    // FINAL RESULT
    // =========================================

    std::cout << "\n";

    std::cout << (failures == 0
                      ? "ALL TESTS PASSED\n"
                      : "SOME TESTS FAILED\n");

    return failures == 0 ? 0 : 1;
}
