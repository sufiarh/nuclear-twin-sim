#include "cli.hpp"
#include <iostream>
#include <iomanip>

void renderCLI(const ReactorState& state) {
    std::cout << "\033[H";
    std::cout << "============================================================\n";
    std::cout << "    NUCLEAR REACTOR DIGITAL TWIN (HIGH-PRECISION RK4)       \n";
    std::cout << "============================================================\n";
    std::cout << " [ELAPSED TIME] : " << std::fixed << std::setprecision(2) << state.time << " s\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << " [CORE PARAMETERS]\n";
    std::cout << "  - Neutron Density     : " << std::scientific << state.neutronDensity << " n/cm3\n";
    std::cout << "  - Reactor Power       : " << std::fixed << std::setprecision(1) << state.powerPercent << " %\n";
    std::cout << "  - Fuel Temperature    : " << std::fixed << std::setprecision(1) << state.fuelTemp << " C\n";
    std::cout << "  - Core Reactivity     : " << std::fixed << std::setprecision(6) << state.reactivity << " dk/k\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << " [INSTRUMENTATION & CONTROL]\n";
    std::cout << "  - Control Rod Position: " << std::fixed << std::setprecision(1) << state.controlRodPos << " % (0=IN, 100=OUT)\n";
    std::cout << "  - Data Logging (.CSV) : ";
    if (state.isLogging) std::cout << "\033[1;33m[ACTIVE] recording to file...\033[0m\n";
    else std::cout << "[INACTIVE] press 'l' to record\n";
    std::cout << "  - Safety RPS Status   : ";
    if (state.scramTripped) std::cout << "\033[1;31m[TRIPPED] " << state.safetyStatus << "\033[0m\n";
    else std::cout << "\033[1;32m[NOMINAL]\033[0m\n";
    std::cout << "============================================================\n";
    std::cout << " [CONTROLS] 'w'=Tarik | 's'=Masukkan | 'x'=SCRAM | 'l'=Log CSV | 'q'=Quit\n";
}
