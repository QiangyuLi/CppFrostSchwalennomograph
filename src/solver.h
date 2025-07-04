#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

// Structure to hold input parameters
// Physical parameter ranges:
// - vpd: Vapor-Pressure Deficit (0.0 to 1.0 psi)
// - nozzle: Nozzle diameter (8 to 64, representing 64ths of an inch)
// - pressure: Nozzle pressure (20 to 80 psi)
// - wind: Wind velocity (0 to 15 mph)
// Expected output range: 0% to 40% evaporation loss
struct Inputs {
    double vpd = 0.6;
    int nozzle = 12;
    double pressure = 40;
    double wind = 5;
};

// Function declarations
double interpolate(const std::vector<std::pair<double, double>>& table, double xq);
double linearBetween(double x, double x1, double y1, double x2, double y2);
double solveEvaporationLoss(const Inputs& in);

#endif // SOLVER_H
