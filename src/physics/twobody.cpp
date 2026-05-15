#include "../../include/physics/twobody.h"
#include "../../include/physics/constants.h"
#include "../../include/physics/state.h"

#include <cmath>

using namespace physics;
using namespace std;

State rates(double       t,
            const State& s )
{
    double rx = s.x2 - s.x1;
    double ry = s.y2 - s.y1;
    double rz = s.z2 - s.z1;
    double r  = sqrt(rx * rx + ry * ry + rz * rz);

    double factor1 = G * m2 / pow(r, 3.0);
    double factor2 = G * m1 / pow(r, 3.0);

    double ax1 =  factor1 * rx;
    double ay1 =  factor1 * ry;
    double az1 =  factor1 * rz;

    double ax2 = -factor2 * rx;
    double ay2 = -factor2 * ry;
    double az2 = -factor2 * rz;

    State dydt = {
        s.vx1, s.vy1, s.vz1,
        s.vx2, s.vy2, s.vz2,
          ax1,   ay1,   az1,
          ax2,   ay2,   az2 };

    return dydt;
}
