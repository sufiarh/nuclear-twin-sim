#include "rps.hpp"

void checkSafetyLimits(ReactorState& state) {
    if (!state.scramTripped) {
        if (state.fuelTemp > 1200.0) {
            state.scramTripped = true;
            state.safetyStatus = "AUTOMATIC SCRAM: OVERTEMPERATURE";
        }
        else if (state.powerPercent > 150.0) {
            state.scramTripped = true;
            state.safetyStatus = "AUTOMATIC SCRAM: OVERPOWER";
        }
    }
}
