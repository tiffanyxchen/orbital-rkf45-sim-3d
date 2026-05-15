#pragma once

#include <vector>

struct State
{
    double  x1,  y1,  z1;
    double  x2,  y2,  z2;
    double vx1, vy1, vz1;
    double vx2, vy2, vz2;
};


std::vector<double> state_to_vector(const State& s);


State vector_to_state(const std::vector<double>& y);


inline State operator-(
    const State& a,
    const State& b)
{
    return
    {
        a.x1  - b.x1,
        a.y1  - b.y1,
        a.z1  - b.z1,

        a.x2  - b.x2,
        a.y2  - b.y2,
        a.z2  - b.z2,

        a.vx1 - b.vx1,
        a.vy1 - b.vy1,
        a.vz1 - b.vz1,

        a.vx2 - b.vx2,
        a.vy2 - b.vy2,
        a.vz2 - b.vz2
    };
}


inline State operator+(
    const State& a,
    const State& b)
{
    return
    {
        a.x1  + b.x1,
        a.y1  + b.y1,
        a.z1  + b.z1,

        a.x2  + b.x2,
        a.y2  + b.y2,
        a.z2  + b.z2,

        a.vx1 + b.vx1,
        a.vy1 + b.vy1,
        a.vz1 + b.vz1,

        a.vx2 + b.vx2,
        a.vy2 + b.vy2,
        a.vz2 + b.vz2
    };
}


inline State operator*(
    double scalar,
    const State& s )
{
    return
    {
        s.x1  * scalar,
        s.y1  * scalar,
        s.z1  * scalar,

        s.x2  * scalar,
        s.y2  * scalar,
        s.z2  * scalar,

        s.vx1 * scalar,
        s.vy1 * scalar,
        s.vz1 * scalar,

        s.vx2 * scalar,
        s.vy2 * scalar,
        s.vz2 * scalar
    };
}