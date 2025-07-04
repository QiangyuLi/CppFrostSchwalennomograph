/*
 * Ultra-Minimal Evaporation Loss Calculator
 * Header-only, single function, no dependencies except std library
 * Just copy this file and #include it in your project
 * 
 * Usage: double loss = calculateEvaporationLoss(vpd, nozzle, pressure, wind);
 * 
 * Parameters:
 * - vpd: Vapor-Pressure Deficit (psi)
 * - nozzle: Nozzle diameter (64ths inch)  
 * - pressure: Pressure (psi)
 * - wind: Wind velocity (mph)
 * 
 * Returns: Evaporation loss percentage
 */

#ifndef EVAP_CALCULATOR_H
#define EVAP_CALCULATOR_H

#include <vector>
#include <algorithm>

inline double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind) {
    // Helper function for linear interpolation
    auto lerp = [](double x, double x1, double y1, double x2, double y2) {
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    };
    
    // Helper function for table lookup with interpolation
    auto interpolate = [](const std::vector<std::pair<double, double>>& table, double x) {
        if (x <= table[0].first) return table[0].second;
        if (x >= table.back().first) return table.back().second;
        
        auto it = std::lower_bound(table.begin(), table.end(), x,
            [](const auto& a, double val) { return a.first < val; });
        
        auto [x2, y2] = *it;
        auto [x1, y1] = *(it - 1);
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    };
    
    // Nomograph lookup tables
    static const std::vector<std::pair<double, double>> S3 = {
        {0,0}, {0.1,0.221}, {0.2,0.381}, {0.3,0.508}, {0.4,0.613}, 
        {0.5,0.695}, {0.6,0.762}, {0.7,0.829}, {0.8,0.887}, {0.9,0.949}, {1.0,1.0}
    };
    static const std::vector<std::pair<double, double>> S5 = {
        {8,1.002}, {10,0.895}, {12,0.815}, {14,0.742}, {16,0.675}, {20,0.563}, 
        {24,0.483}, {32,0.352}, {40,0.233}, {48,0.152}, {64,-0.001}
    };
    static const std::vector<std::pair<double, double>> S7 = {
        {20,0.0}, {25,0.159}, {30,0.296}, {35,0.407}, {40,0.499}, {45,0.589}, 
        {50,0.665}, {55,0.735}, {60,0.800}, {70,0.900}, {80,0.996}
    };
    static const std::vector<std::pair<double, double>> S9 = {
        {0,0.0}, {1,0.140}, {2,0.246}, {3,0.356}, {4,0.435}, {5,0.508}, 
        {6,0.578}, {7,0.651}, {8,0.706}, {9,0.760}, {10,0.811}, {11,0.854}, 
        {12,0.895}, {13,0.930}, {15,0.994}
    };
    static const std::vector<std::pair<double, double>> S6_flip = {
        {0.102,0}, {0.252,0.5}, {0.360,1}, {0.460,2}, {0.521,3}, {0.563,4}, 
        {0.599,5}, {0.633,6}, {0.671,8}, {0.702,10}, {0.758,15}, {0.812,20}, 
        {0.883,30}, {0.917,40}
    };
    
    // Column positions
    constexpr double x3 = 0.0, x4 = 0.237, x5 = 0.439, x6 = 0.490, 
                     x7 = 0.738, x8 = 0.870, x9 = 1.000;
    
    // Calculate Y coordinates for each parameter
    double y3 = interpolate(S3, vpd);
    double y5 = interpolate(S5, nozzle);
    double y7 = interpolate(S7, pressure);
    double y9 = interpolate(S9, wind);
    
    // Calculate nomograph intersection
    double yA = lerp(x4, x3, y3, x5, y5);
    double yB = lerp(x8, x7, y7, x9, y9);
    double yL = lerp(x6, x4, yA, x8, yB);
    
    // Return final result
    return interpolate(S6_flip, yL);
}

#endif // EVAP_CALCULATOR_H
