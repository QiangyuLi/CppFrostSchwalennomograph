#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

// Structure to hold input parameters
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
