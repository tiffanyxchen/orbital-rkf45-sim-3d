#include "../../include/utils/math_utils.h"

#include <cmath>
#include <algorithm>

using namespace std;

double max_abs(const vector<double>& v)
{
    double m = 0.0;

    for (double val : v)
    {
        m = max(m, abs(val));
    }

    return m;
}
