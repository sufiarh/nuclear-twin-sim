#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "reactor_state.hpp"

// Struktur pembantu untuk menyimpan turunan matematika (derivatives)
struct Derivatives {
    double dn;
    double dc;
    double dTf;
};

void updateReactorPhysicsRK4(ReactorState& state, double dt);

#endif
