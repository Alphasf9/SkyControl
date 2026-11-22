#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Aircraft.h"
#include "Physics.h"
#include "SimulationClock.h"
#include "Commands.h"

std::vector<Aircraft> spawnAircraft(int count)
{
    std::vector<Aircraft> fleet;

    for (int i = 0; i < count; i++)
    {
        Aircraft ac;

        std::ostringstream id;
        id << "AC-" << (1001 + i);
        ac.id = id.str();

        std::ostringstream flight;
        flight << "SK-" << (101 + i);
        ac.flightNumber = flight.str();

        ac.x = -45.0 + i * 10.0;
        ac.y = (i % 2) * 20.0;
        ac.altitudeFt = 5000.0 + i * 1000.0;
        ac.speedKnots = 200.0 + i * 20.0;
        ac.headingDeg = i * 36.0;

        // NEW: Initialize turning data
        ac.targetHeadingDeg = ac.headingDeg;
        ac.turnRateDegPerSec = 3.0;

        fleet.push_back(ac);
    }

    return fleet;
}
int main()
{
    // 1. Create 10 aircraft
    std::vector<Aircraft> fleet = spawnAircraft(10);

    // 2. Create simulation clock
    SimulationClock clock(10.0);

    std::cout << std::fixed << std::setprecision(2);

    // 3. Issue heading commands
    CommandResult r1 = commandHeading(fleet[0], 90.0);
    CommandResult r2 = commandHeading(fleet[1], 500.0);

    std::cout << "Command to AC-1001: " << toString(r1) << "\n";
    std::cout << "Command to AC-1002: " << toString(r2) << "\n";

    // 4. Run simulation
    for (int step = 0; step < 6; step++)
    {
        for (Aircraft& ac : fleet)
        {
            updateHeading(ac, clock.dt());
            updatePosition(ac, clock.dt());
        }

        clock.tick();

        std::cout << "--- t = "
                  << clock.simTimeSeconds() << "s ---\n";

        for (const Aircraft& ac : fleet)
        {
            std::cout << ac.id
                      << " | HDG: " << ac.headingDeg
                      << " | X: " << ac.x
                      << " | Y: " << ac.y << "\n";
        }
    }

    return 0;
}