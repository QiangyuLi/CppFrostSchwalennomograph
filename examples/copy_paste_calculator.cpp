/*
 * COPY-PASTE EVAPORATION CALCULATOR
 * 
 * Just copy this function into your project - no includes needed except <vector> and <algorithm>
 * 
 * Usage: double loss = calculateEvaporationLoss(vpd, nozzle, pressure, wind);
 */

#include <vector>
#include <algorithm>
#include <iostream>

double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind) {
    // Nomograph data (pre-computed, S6 flipped for efficiency)
    static const std::vector<std::pair<double, double>> 
        S3{{0,0},{0.1,0.221},{0.2,0.381},{0.3,0.508},{0.4,0.613},{0.5,0.695},{0.6,0.762},{0.7,0.829},{0.8,0.887},{0.9,0.949},{1.0,1.0}},
        S5{{8,1.002},{10,0.895},{12,0.815},{14,0.742},{16,0.675},{20,0.563},{24,0.483},{32,0.352},{40,0.233},{48,0.152},{64,-0.001}},
        S7{{20,0.0},{25,0.159},{30,0.296},{35,0.407},{40,0.499},{45,0.589},{50,0.665},{55,0.735},{60,0.800},{70,0.900},{80,0.996}},
        S9{{0,0.0},{1,0.140},{2,0.246},{3,0.356},{4,0.435},{5,0.508},{6,0.578},{7,0.651},{8,0.706},{9,0.760},{10,0.811},{11,0.854},{12,0.895},{13,0.930},{15,0.994}},
        S6{{0.102,0},{0.252,0.5},{0.360,1},{0.460,2},{0.521,3},{0.563,4},{0.599,5},{0.633,6},{0.671,8},{0.702,10},{0.758,15},{0.812,20},{0.883,30},{0.917,40}};
    
    // Table lookup with linear interpolation
    auto interp = [](const std::vector<std::pair<double, double>>& t, double x) {
        if (x <= t[0].first) return t[0].second;
        if (x >= t.back().first) return t.back().second;
        auto it = std::lower_bound(t.begin(), t.end(), x, [](const auto& a, double v) { return a.first < v; });
        auto [x2, y2] = *it; auto [x1, y1] = *(it - 1);
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    };
    
    // Column positions and calculations
    double y3 = interp(S3, vpd), y5 = interp(S5, nozzle), y7 = interp(S7, pressure), y9 = interp(S9, wind);
    double yA = y3 + (y5 - y3) * 0.237 / 0.439, yB = y7 + (y9 - y7) * 0.132 / 0.262;
    double yL = yA + (yB - yA) * 0.253 / 0.633;
    
    return interp(S6, yL);
}

// Example usage
int main() {
    std::cout << "Copy-paste calculator test:\n";
    std::cout << "Loss: " << calculateEvaporationLoss(0.6, 12, 40, 5) << "%\n";
    return 0;
}
