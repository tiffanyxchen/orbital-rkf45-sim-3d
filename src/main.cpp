#include "../include/integrators/rkf45.h"
#include "../include/physics/twobody.h"
#include "../include/physics/state.h"

#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    State y0 =
    {
           0.0, 0.0,   0.0,
        3000.0, 0.0,   0.0,

          10.0, 20.0, 30.0,
           0.0, 40.0,  0.0
    };

    double        t0 =   0.0 ;
    double        tf = 480.0 ;
    double tolerance = 1.0e-8;

    vector<double> tout;
    vector<State>  yout;

    rkf45(
        rates,
        t0,
        tf,
        y0,
        tolerance,
        tout,
        yout
    );

    ofstream file("../output/trajectory.csv");

    for (size_t i = 0; i < tout.size(); i++)
    {
        file << tout[i];

        vector<double> y = state_to_vector(yout[i]);
        for (double val : y)
        {
            file << "," << val;
        }
        
        file << "\n";
    }


    file.close();

    cout << "Simulation complete.\n";

    return 0;
}
