# Nuclear Reactor Digital Twin (PWR)

A technical implementation of a Pressurized Water Reactor (PWR) core dynamics simulator. Developed in C++ using RK4 numerical integration for real-time transient analysis.

## ⚙️ Technical Overview
This project simulates reactor kinetics and thermal-hydraulic coupling. The focus is on deterministic, low-latency performance suitable for safety-critical I&C logic testing.

![Technical Sketch](pwr%20d%20twin%20ic.png)

## 📐 Core Physics Models

The simulator solves the Point Reactor Kinetics Equations (PRKE) with feedback:

**Neutron Kinetics:**
$$\frac{dn}{dt} = \frac{\rho(t) - \beta}{\Lambda}n(t) + \lambda C(t)$$
$$\frac{dC}{dt} = \frac{\beta}{\Lambda}n(t) - \lambda C(t)$$

**Reactivity Feedback:**
$$\rho(t) = \rho_{\text{rod}} + \alpha_f (T_f(t) - T_{f,0})$$

**Thermal Coupling:**
$$\frac{dT_f}{dt} = \gamma \cdot P(t) - h(T_f(t) - T_m)$$

## 🚀 Deployment
1. **Compile:**
   ```bash
   mkdir build && cd build
   cmake .. && make
2. Execute
   ./nuclear_sim
3. **Data Acquisition:** Press `l` during simulation to log transient data to `reactor_transient_data.csv`.

## 📝 Engineering Notes
This project serves as a sandbox for implementing Reactor Protection System (RPS) logic. The integration of RK4 ensures that the system response remains stable during sharp power transients—a critical requirement when modeling fuel temperature feedbacks.

---
*Project maintained for research and academic exploration. Contributions to the physics solver or optimization of the I&C logic are welcome.*
