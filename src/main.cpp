#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "reactor_state.hpp"
#include "physics.hpp"
#include "input.hpp"
#include "rps.hpp"
#include "cli.hpp"

int main() {
    ReactorState reactor;
    double dt = 0.05;
    std::ofstream csvFile;

    std::cout << "\033[2J"; // Clear screen di awal

    while (true) {
        if (kbhit()) {
            char key = getchar();
            if (key == 'q') break;

            // Kontrol Logging CSV toggling
            if (key == 'l' || key == 'L') {
                if (!reactor.isLogging) {
                    csvFile.open("reactor_transient_data.csv");
                    csvFile << "Time,PowerPercent,FuelTemp,Reactivity,ControlRodPos\n"; // Header CSV
                    reactor.isLogging = true;
                } else {
                    csvFile.close();
                    reactor.isLogging = false;
                }
            }

            if (!reactor.scramTripped) {
                if (key == 'w' || key == 'W') reactor.controlRodPos += 1.0;
                if (key == 's' || key == 'S') reactor.controlRodPos -= 1.0;
                if (key == 'x' || key == 'X') {
                    reactor.scramTripped = true;
                    reactor.safetyStatus = "MANUAL EMERGENCY SCRAM TRIPPED";
                }
                if (reactor.controlRodPos > 100.0) reactor.controlRodPos = 100.0;
                if (reactor.controlRodPos < 0.0) reactor.controlRodPos = 0.0;
            }
        }

        // Jalankan solver RK4
        updateReactorPhysicsRK4(reactor, dt);
        checkSafetyLimits(reactor);
        renderCLI(reactor);

        // Jika fitur log aktif, tulis data ke file CSV setiap langkah waktu (time-step)
        if (reactor.isLogging && csvFile.is_open()) {
            csvFile << reactor.time << ","
            << reactor.powerPercent << ","
            << reactor.fuelTemp << ","
            << reactor.reactivity << ","
            << reactor.controlRodPos << "\n";
        }

        reactor.time += dt;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    if (csvFile.is_open()) csvFile.close();
    std::cout << "\nSimulator terminated safely. Data logged successfully if active.\n";
    return 0;
}
