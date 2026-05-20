#include "physics.hpp"
#include <cmath>

// Fungsi untuk menghitung turunan pada titik tertentu (sistem persamaan diferensial terikat)
Derivatives computeDerivatives(double n, double c, double Tf, double controlRodPos) {
    Derivatives der;

    // 1. Hitung Reaktivitas (Batang kendali + Umpan Balik Doppler)
    double rho_rod = (controlRodPos - 50.0) * 0.00015; // Sensitivitas batang kendali yang disesuaikan
    double rho_feedback = ALPHA_F * (Tf - T_FUEL_REF);
    double reactivity = rho_rod + rho_feedback;

    // 2. Persamaan Kinetika Reaktor (PRKE)
    der.dn = ((reactivity - BETA) / LIFETIME) * n + LAMBDA * c;
    der.dc = (BETA / LIFETIME) * n - LAMBDA * c;

    // 3. Persamaan Termal-Hidrolika (Daya ke Suhu)
    double powerPercent = n * POWER_CONV;
    double heat_generated = powerPercent * 0.45; // Faktor skala pembangkitan panas
    double heat_removed = HEAT_TRANSFER_COEFF * (Tf - COOLANT_TEMP);
    der.dTf = (heat_generated - heat_removed) * 100.0; // Kapasitas panas termodifikasi

    return der;
}

void updateReactorPhysicsRK4(ReactorState& state, double dt) {
    // Penanganan gerak batang kendali saat SCRAM otomatis jatuh dalam 1.5 detik
    if (state.scramTripped) {
        if (state.controlRodPos > 0.0) state.controlRodPos -= 150.0 * dt;
        if (state.controlRodPos < 0.0) state.controlRodPos = 0.0;
    }

    // --- ALGORITMA RUNGE-KUTTA ORDE 4 (RK4) ---
    double n0 = state.neutronDensity;
    double c0 = state.precursorDensity;
    double Tf0 = state.fuelTemp;
    double rod = state.controlRodPos;

    // K1
    Derivatives k1 = computeDerivatives(n0, c0, Tf0, rod);

    // K2
    Derivatives k2 = computeDerivatives(n0 + 0.5 * dt * k1.dn,
                                        c0 + 0.5 * dt * k1.dc,
                                        Tf0 + 0.5 * dt * k1.dTf, rod);

    // K3
    Derivatives k3 = computeDerivatives(n0 + 0.5 * dt * k2.dn,
                                        c0 + 0.5 * dt * k2.dc,
                                        Tf0 + 0.5 * dt * k2.dTf, rod);

    // K4
    Derivatives k4 = computeDerivatives(n0 + dt * k3.dn,
                                        c0 + dt * k3.dc,
                                        Tf0 + dt * k3.dTf, rod);

    // Update Nilai Akhir State berdasarkan rata-rata tertimbang RK4
    state.neutronDensity   += (dt / 6.0) * (k1.dn + 2.0 * k2.dn + 2.0 * k3.dn + k4.dn);
    state.precursorDensity += (dt / 6.0) * (k1.dc + 2.0 * k2.dc + 2.0 * k3.dc + k4.dc);
    state.fuelTemp         += (dt / 6.0) * (k1.dTf + 2.0 * k2.dTf + 2.0 * k3.dTf + k4.dTf);

    // Proteksi nilai fisik dari batas bawah (underflow)
    if (state.neutronDensity < 0.0) state.neutronDensity = 0.0;
    if (state.precursorDensity < 0.0) state.precursorDensity = 0.0;

    // Update parameter output sekunder
    state.powerPercent = state.neutronDensity * POWER_CONV;

    // Update reaktivitas akhir untuk kebutuhan visualisasi display
    double rho_rod = (state.controlRodPos - 50.0) * 0.00015;
    double rho_feedback = ALPHA_F * (state.fuelTemp - T_FUEL_REF);
    state.reactivity = rho_rod + rho_feedback;
}
