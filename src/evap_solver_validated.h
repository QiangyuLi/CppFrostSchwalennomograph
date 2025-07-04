#ifndef EVAP_SOLVER_VALIDATED_H
#define EVAP_SOLVER_VALIDATED_H

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace EvapSolverValidated {

// Input structure with validation
struct Input {
    double vpd;      // Vapor-Pressure Deficit (psi): 0.0 to 1.0
    int nozzle;      // Nozzle diameter (64ths inch): 8 to 64  
    double pressure; // Pressure (psi): 20 to 80
    double wind;     // Wind velocity (mph): 0 to 15
    
    // Constructor with validation
    Input(double vpd_val, int nozzle_val, double pressure_val, double wind_val) 
        : vpd(vpd_val), nozzle(nozzle_val), pressure(pressure_val), wind(wind_val) {
        validate();
    }
    
    // Default constructor
    Input() : vpd(0.6), nozzle(12), pressure(40), wind(5) {}
    
    // Validation function
    void validate() const {
        if (vpd < 0.0 || vpd > 1.0) {
            throw std::runtime_error("Vapor-Pressure Deficit must be between 0.0 and 1.0 psi (got " + std::to_string(vpd) + ")");
        }
        if (nozzle < 8 || nozzle > 64) {
            throw std::runtime_error("Nozzle diameter must be between 8 and 64 (64ths of an inch) (got " + std::to_string(nozzle) + ")");
        }
        if (pressure < 20 || pressure > 80) {
            throw std::runtime_error("Nozzle pressure must be between 20 and 80 psi (got " + std::to_string(pressure) + ")");
        }
        if (wind < 0 || wind > 15) {
            throw std::runtime_error("Wind velocity must be between 0 and 15 mph (got " + std::to_string(wind) + ")");
        }
    }
};

// Validation result structure
struct ValidationResult {
    bool isValid;
    std::string errorMessage;
    double calculatedValue;
    bool isOutOfRange;
    
    ValidationResult(bool valid, const std::string& error = "", double value = 0.0, bool outOfRange = false)
        : isValid(valid), errorMessage(error), calculatedValue(value), isOutOfRange(outOfRange) {}
};

// Validated evaporation loss calculator
class Calculator {
private:
    // Linear interpolation
    static double lerp(const std::vector<std::pair<double, double>>& table, double x) {
        if (table.empty()) throw std::runtime_error("Empty interpolation table");
        if (x <= table.front().first) return table.front().second;
        if (x >= table.back().first) return table.back().second;
        
        auto it = std::lower_bound(table.begin(), table.end(), x,
            [](const auto& a, double val) { return a.first < val; });
        
        auto [x2, y2] = *it;
        auto [x1, y1] = *(it - 1);
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    }
    
    // Linear interpolation between two points
    static double lerp2(double x, double x1, double y1, double x2, double y2) {
        return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
    }

public:
    // Calculate evaporation loss with validation
    static ValidationResult calculateWithValidation(const Input& in) {
        try {
            // Validate input
            in.validate();
            
            // Perform calculation
            double result = calculateUnchecked(in);
            
            // Check if result is within expected range
            bool outOfRange = (result < 0.0 || result > 40.0);
            
            return ValidationResult(true, "", result, outOfRange);
            
        } catch (const std::exception& e) {
            return ValidationResult(false, e.what(), 0.0, false);
        }
    }
    
    // Calculate evaporation loss (throws on invalid input)
    static double calculate(const Input& in) {
        in.validate();
        return calculateUnchecked(in);
    }
    
    // Calculate without validation (for internal use)
    static double calculateUnchecked(const Input& in) {
        // Nomograph data tables
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
        static const std::vector<std::pair<double, double>> S6 = {
            {0,0.102}, {0.5,0.252}, {1,0.360}, {2,0.460}, {3,0.521}, {4,0.563}, 
            {5,0.599}, {6,0.633}, {8,0.671}, {10,0.702}, {15,0.758}, {20,0.812}, 
            {30,0.883}, {40,0.917}
        };
        
        // Column X coordinates
        constexpr double x3 = 0.0, x4 = 0.237, x5 = 0.439, x6 = 0.490, 
                        x7 = 0.738, x8 = 0.870, x9 = 1.000;
        
        // Interpolate Y coordinates
        double y3 = lerp(S3, in.vpd);
        double y5 = lerp(S5, in.nozzle);
        double y7 = lerp(S7, in.pressure);
        double y9 = lerp(S9, in.wind);
        
        // Calculate pivot points and intersection
        double yA = lerp2(x4, x3, y3, x5, y5);
        double yB = lerp2(x8, x7, y7, x9, y9);
        double yL = lerp2(x6, x4, yA, x8, yB);
        
        // Reverse interpolation on S6 (flip x/y)
        static std::vector<std::pair<double, double>> S6_flip;
        if (S6_flip.empty()) {
            for (const auto& [val, y] : S6) S6_flip.emplace_back(y, val);
            std::sort(S6_flip.begin(), S6_flip.end());
        }
        
        return lerp(S6_flip, yL);
    }
    
    // Get valid parameter ranges
    static std::string getParameterRanges() {
        return "Valid Parameter Ranges:\n"
               "• Vapor-Pressure Deficit (VPD): 0.0 to 1.0 psi\n"
               "• Nozzle Diameter: 8 to 64 (64ths of an inch)\n"
               "• Nozzle Pressure: 20 to 80 psi\n"
               "• Wind Velocity: 0 to 15 mph\n"
               "• Expected Evaporation Loss: 0% to 40%";
    }
};

// Convenience functions with validation
inline ValidationResult calculateEvaporationLossWithValidation(double vpd, int nozzle, double pressure, double wind) {
    try {
        Input input(vpd, nozzle, pressure, wind);
        return Calculator::calculateWithValidation(input);
    } catch (const std::exception& e) {
        return ValidationResult(false, e.what(), 0.0, false);
    }
}

inline double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind) {
    Input input(vpd, nozzle, pressure, wind);
    return Calculator::calculate(input);
}

// Safe convenience function that returns a default value on error
inline double calculateEvaporationLossSafe(double vpd, int nozzle, double pressure, double wind, double defaultValue = 0.0) {
    try {
        return calculateEvaporationLoss(vpd, nozzle, pressure, wind);
    } catch (const std::exception&) {
        return defaultValue;
    }
}

} // namespace EvapSolverValidated

#endif // EVAP_SOLVER_VALIDATED_H
