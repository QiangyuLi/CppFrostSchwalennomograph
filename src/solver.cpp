#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Linear interpolation helper
double interpolate(const std::vector<std::pair<double, double>>& table, double xq) {
    if (table.empty()) throw std::runtime_error("Interpolation table is empty.");

    auto comp = [](const std::pair<double, double>& a, double x) {
        return a.first < x;
    };

    if (xq <= table.front().first) return table.front().second;
    if (xq >= table.back().first) return table.back().second;

    auto it = std::lower_bound(table.begin(), table.end(), xq, comp);
    auto [x1, y1] = *(it - 1);
    auto [x2, y2] = *it;
    return y1 + (y2 - y1) * (xq - x1) / (x2 - x1);
}

// Linear interpolation between two points
double linearBetween(double x, double x1, double y1, double x2, double y2) {
    double slope = (y2 - y1) / (x2 - x1);
    return y1 + slope * (x - x1);
}

// Compute evaporation loss
double solveEvaporationLoss(const Inputs& in) {
    // Tick data
    std::vector<std::pair<double, double>> S3 = {{0, 0}, {0.1, 0.221}, {0.2, 0.381}, {0.3, 0.508}, {0.4, 0.613}, {0.5, 0.695}, {0.6, 0.762}, {0.7, 0.829}, {0.8, 0.887}, {0.9, 0.949}, {1.0, 1.0}};
    std::vector<std::pair<double, double>> S5 = {{8, 1.002}, {10, 0.895}, {12, 0.815}, {14, 0.742}, {16, 0.675}, {20, 0.563}, {24, 0.483}, {32, 0.352}, {40, 0.233}, {48, 0.152}, {64, -0.001}};
    std::vector<std::pair<double, double>> S7 = {{20, 0.0}, {25, 0.159}, {30, 0.296}, {35, 0.407}, {40, 0.499}, {45, 0.589}, {50, 0.665}, {55, 0.735}, {60, 0.800}, {70, 0.900}, {80, 0.996}};
    std::vector<std::pair<double, double>> S9 = {{0, 0.0}, {1, 0.140}, {2, 0.246}, {3, 0.356}, {4, 0.435}, {5, 0.508}, {6, 0.578}, {7, 0.651}, {8, 0.706}, {9, 0.760}, {10, 0.811}, {11, 0.854}, {12, 0.895}, {13, 0.930}, {15, 0.994}};
    std::vector<std::pair<double, double>> S6 = {{0, 0.102}, {0.5, 0.252}, {1, 0.360}, {2, 0.460}, {3, 0.521}, {4, 0.563}, {5, 0.599}, {6, 0.633}, {8, 0.671}, {10, 0.702}, {15, 0.758}, {20, 0.812}, {30, 0.883}, {40, 0.917}};

    // X coordinates of columns
    double x3 = 0.0, x4 = 0.237, x5 = 0.439;
    double x6 = 0.490;
    double x7 = 0.738, x8 = 0.870, x9 = 1.000;

    // Interpolate Y coordinates
    double y3 = interpolate(S3, in.vpd);
    double y5 = interpolate(S5, in.nozzle);
    double y7 = interpolate(S7, in.pressure);
    double y9 = interpolate(S9, in.wind);

    // Compute pivot points A and B
    double yA = linearBetween(x4, x3, y3, x5, y5);
    double yB = linearBetween(x8, x7, y7, x9, y9);

    // Intersect at column 6
    double yL = linearBetween(x6, x4, yA, x8, yB);

    // Reverse interpolation on S6 (need to flip x/y)
    std::vector<std::pair<double, double>> S6_flip;
    for (const auto& [val, y] : S6)
        S6_flip.emplace_back(y, val);
    std::sort(S6_flip.begin(), S6_flip.end());

    double evapLoss = interpolate(S6_flip, yL);

    std::cout << "Evaporation Loss: " << evapLoss << "%" << std::endl;
    return evapLoss;
}
