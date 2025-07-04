#include "solver.h"

// Example usage
int main() {
    Inputs inputs;
    inputs.vpd = 0.6;
    inputs.nozzle = 12;
    inputs.pressure = 40;
    inputs.wind = 5;

    solveEvaporationLoss(inputs);
    return 0;
}
