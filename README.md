# Nuclear Reactor Digital Twin & Real-Time Simulator

[![C++17](https://img.shields.io/badge/language-C++17-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A laboratory-grade **Digital Twin** and **Real-Time I&C (Instrumentation & Control) Simulator** for a Pressurized Water Reactor (PWR) core, developed in pure C++. This project simulates reactor kinetics and thermal-hydraulics using **4th Order Runge-Kutta (RK4)** numerical integration, providing high-fidelity transient analysis.

## 🚀 Key Features
- **High-Fidelity Physics Engine:** Coupled Point Reactor Kinetics Equations (PRKE) with thermal-Doppler feedback loops.
- **Deterministic Solver:** Implements RK4 numerical integration for stability in stiff differential equations.
- **Real-Time I&C Logic:** Built-in Reactor Protection System (RPS) with <50ms response time for automated SCRAM scenarios.
- **Data Export:** Integrated logging engine to export transient data to `.csv` for performance analysis.
- **Interactive CLI:** Low-latency terminal interface with ANSI-based rendering and non-blocking I/O.

## 📊 Transient Analysis
The simulator captures real-time data to visualize reactor behavior during power transients or emergency shutdown scenarios.

*(Once you run the simulation and plot data, upload your image here)*
`![Transient Plot](reactor_transient_plot.png)`

## 🛠 Prerequisites
- **Compiler:** GCC (with C++17 support)
- **Build System:** CMake 3.10+
- **Python (Optional):** Required for generating plots (`matplotlib`, `pandas`)

## 💻 Getting Started

### 1. Build the project
```bash
mkdir build && cd build
cmake ..
make
