#include "../../include/integrators/rkf45.h"
#include "../../include/utils/math_utils.h"
#include "../../include/physics/state.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
==========================================
Fehlberg coefficients
==========================================
*/

namespace{
    constexpr double a[6] = {
        0.0, 1.0/4.0, 3.0/8.0, 12.0/13.0, 1.0, 1.0/2.0
    };

    constexpr double b[6][5] ={
        {0,0,0,0,0},
        {1.0/4.0,0,0,0,0},
        {3.0/32.0,9.0/32.0,0,0,0},
        {1932.0/2197.0,-7200.0/2197.0,7296.0/2197.0,0,0},
        {439.0/216.0,-8.0,3680.0/513.0,-845.0/4104.0,0},
        {-8.0/27.0,2.0,-3544.0/2565.0,1859.0/4104.0,-11.0/40.0}
    };

    constexpr double c4[6] = {
        25.0/216.0,0,1408.0/2565.0,2197.0/4104.0,-1.0/5.0,0
    };

    constexpr double c5[6] = {
        16.0/135.0,0,6656.0/12825.0,28561.0/56430.0,-9.0/50.0,2.0/55.0
    };
}
   

/* 1
==========================================
computeStages()

Computes the six intermediate RKF45
stages.

Each stage estimates the derivative
at a different point inside the
current timestep.
==========================================
*/

void computeStages(

    ODEFunction ode_function,
    double t,
    double h,
    const State& y,
    State f[6]
) {

    for (int i = 0; i < 6; i++) {

        State y_inner = y;

        // y_inner = y + h * Σ(b[i][j] * k[j])
        
        for (int j = 0; j < i; j++) {

            y_inner = y_inner + h * b[i][j] * f[j];

        }
    
        double t_inner = t + a[i] * h;

        f[i] = ode_function(t_inner, y_inner);
    }
}

/* 2
==========================================
computeSolution()

Builds either the 4th-order or
5th-order RKF45 solution using the
supplied coefficient set.
==========================================
*/

State computeSolution(

    const State& y,
    State f[6],
    const double coeffs[6],
    double h
) {

    State result = y;

    for (int i = 0; i < 6; i++) {

        result = result + h * coeffs[i] * f[i];
        
    }

    return result;
}

/* 3
==========================================
computeError()

Estimates the local truncation error
from the difference between the
4th-order and 5th-order solutions.
==========================================
*/

double computeError(const State& y4, const State& y5) {
    
    State te = y5 - y4;
    
    return max_abs(state_to_vector(te));
}

/* 4
==========================================
rkf45()

Adaptive Runge-Kutta-Fehlberg
4th/5th-order integrator.

Automatically adjusts timestep size
to satisfy the requested tolerance.
==========================================
*/

void rkf45(

    ODEFunction ode_function,
    double t0,
    double tf,
    const State& y0,
    double tolerance,
    vector<double>& tout,
    vector<State>& yout
) {

    double t = t0;
    State  y = y0;

    // Initial timestep
    double h = (tf - t0) / 100.0;

    // Store initial condition
    tout.push_back(t);
    yout.push_back(y);

    /*
    ======================================
    Main integration loop
    ======================================
    */

    while (t < tf) {

        // Prevent overshooting final time
        if (t + h > tf) { h = tf - t;}

        State f[6];
        // Compute RK stages
        computeStages(ode_function,t,h,y,f);


        // 4th-order, 5th-order solution
        State y4 = computeSolution(y, f, c4, h);
        State y5 = computeSolution(y, f, c5, h);


        // Error estimate
        double te_max = computeError(y4, y5);

        double ymax       = max_abs(state_to_vector(y));
        double te_allowed = tolerance * max(ymax, 1.0);

        /*
        ======================================
        Adaptive timestep scaling
        ======================================
        */

        double delta = pow(te_allowed/(te_max + 1e-15), 1.0 / 5.0);

        // Accept timestep

        if (te_max <= te_allowed) {

            t += h;
            y = y5;

            tout.push_back(t);
            yout.push_back(y);
        }

        // Update timestep

        h = max(0.1 * h, min(delta * h, 4.0 * h));

        // Prevent timestep collapse
        
        // hmin is minimum timestep: 2.22*10^-16
        double hmin = 16.0 * numeric_limits<double>::epsilon();

        if (abs(h) < hmin) {

            cerr << "Step size too small.\n";

            break;
        }
    }
}