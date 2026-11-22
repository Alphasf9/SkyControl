#pragma once

#include "Aircraft.h"

enum class CommandResult
{
    ACCEPTED,
    REJECTED_INVALID_VALUE
};

CommandResult commandHeading(Aircraft &ac, double headingDeg);

const char *toString(CommandResult result);