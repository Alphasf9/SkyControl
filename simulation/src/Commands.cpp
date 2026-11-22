#include "Commands.h"
#include "Physics.h"

CommandResult commandHeading(Aircraft &ac, double headingDeg)
{
    if (!(headingDeg >= 0.0 && headingDeg <= 360))
    {
        return CommandResult::REJECTED_INVALID_VALUE;
    }

    ac.targetHeadingDeg = normalizeHeading(headingDeg);
    return CommandResult::ACCEPTED;
};

const char *toString(CommandResult result)
{
    switch (result)
    {
    case CommandResult::ACCEPTED:
        return "ACCEPTED";
    case CommandResult::REJECTED_INVALID_VALUE:
        return "REJECTED_INVALID_VALUE";
    }

    return "UNKNOWN";
}