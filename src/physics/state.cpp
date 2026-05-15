#include "../../include/physics/state.h"

using namespace std;

vector<double> state_to_vector(const State& s)
{
    return
    {
        s.x1 , s.y1 , s.z1,
        s.x2 , s.y2 , s.z2,
        s.vx1, s.vy1, s.vz1,
        s.vx2, s.vy2, s.vz2
    };
}

State vector_to_state(const vector<double>& y)
{
    State s;

    s.x1  = y[0]; s.y1  = y[1]; s.z1  = y[2];
    s.x2  = y[3]; s.y2  = y[4]; s.z2  = y[5];

    s.vx1 = y[6]; s.vy1 = y[7]; s.vz1 = y[8];
    s.vx2 = y[9]; s.vy2 = y[10]; s.vz2 = y[11];

    return s;
}
