#pragma once
#include "../physics/state.h"
#include <vector>

typedef State (*ODEFunction)(
    double,
    const State&
);

void rkf45(
    ODEFunction ode_function,
    double t0,
    double tf,
    const State& y0,
    double tolerance,
    std::vector<double>& tout,
    std::vector<State>& yout
);
