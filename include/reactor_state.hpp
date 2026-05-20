#ifndef REACTOR_STATE_HPP
#define REACTOR_STATE_HPP

#include <string>

// --- PARAMETER FISIKA VALID (Dekat dengan Spesifikasi PWR Westinghouse) ---
const double BETA = 0.0065;                  // Fraksi neutron kasif total
const double LAMBDA = 0.08;                  // Konstanta peluruhan rata-rata (s^-1)
const double LIFETIME = 1e-4;                // Waktu hidup neutron cepat (s)
const double ALPHA_F = -2.5e-5;              // Koefisien Doppler Bahan Bakar (dk/k/C)
const double T_FUEL_REF = 290.0;             // Temperatur referensi (C)
const double COOLANT_TEMP = 290.0;           // Temperatur inlet pendingin (C)
const double HEAT_TRANSFER_COEFF = 0.15;     // Koefisien perpindahan panas efektif
const double POWER_CONV = 1e-10;             // Faktor konversi kerapatan neutron ke % Daya

struct ReactorState {
    double time = 0.0;
    double neutronDensity = 1e10;            // Kondisi awal 100% daya
    double precursorDensity = (BETA / (LIFETIME * LAMBDA)) * 1e10;
    double fuelTemp = 600.0;                 // Temperatur operasi nominal bahan bakar (C)
    double powerPercent = 100.0;
    double controlRodPos = 50.0;             // 50% = Kritis nominal
    double reactivity = 0.0;
    bool scramTripped = false;
    bool isLogging = false;                  // Status pencatatan data ke CSV
    std::string safetyStatus = "NOMINAL";
};

#endif
