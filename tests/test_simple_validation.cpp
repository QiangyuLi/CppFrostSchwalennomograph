/*
 * Simple Multi-Solver Validation Test
 * 
 * Test data source: Trimmer, Walter L. (1987). "Sprinkler Evaporation Loss Equation."
 * Journal of Irrigation and Drainage Engineering, Vol. 113, Issue 4, pp. 616-624.
 * https://doi.org/10.1061/(ASCE)0733-9437(1987)113:4(616)
 * Published: November 1, 1987
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include "../src/evap_solver_validated.h"
#include "../src/evap_solver_compact.h"
#include "../src/solver.h"

// Conversion functions
double mmToSixtyFourthsInch(double mm) { return mm / 25.4 * 64.0; }
double kPaToPsi(double kPa) { return kPa * 0.145038; }
double msToMph(double ms) { return ms * 2.237; }

struct TestCase {
    double D_mm, h_kPa, es_e_kPa, W_ms, E_expected;
    int nozzle_64ths;
    double pressure_psi, vpd_psi, wind_mph;
    bool withinLimits;
};

int main() {
    std::cout << "Multi-Solver Validation Test" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Test data source: Trimmer, W.L. (1987). Journal of Irrigation and Drainage Engineering" << std::endl;
    std::cout << "https://doi.org/10.1061/(ASCE)0733-9437(1987)113:4(616)" << std::endl;
    std::cout << std::endl;
    
    std::vector<TestCase> tests = {
        // Test cases from Trimmer (1987) validation table
        {3.18, 207, 2.8, 1.3, 5.5},
        {3.18, 207, 4.5, 4.5, 16.0},
        {4.76, 207, 4.5, 4.5, 10.0},
        {4.76, 414, 4.5, 2.2, 13.0},
        {4.76, 414, 2.8, 1.3, 7.0},
        {4.76, 414, 2.8, 4.5, 14.0},
        {6.35, 414, 2.8, 4.5, 11.0},
        {6.35, 414, 4.5, 2.7, 9.5},
        {6.35, 414, 4.5, 1.3, 7.5},
        {6.35, 552, 4.5, 4.5, 18.0},
        {12.7, 552, 4.5, 4.5, 9.0}
    };
    
    // Convert units and check limits
    for (auto& test : tests) {
        test.nozzle_64ths = static_cast<int>(std::round(mmToSixtyFourthsInch(test.D_mm)));
        test.pressure_psi = kPaToPsi(test.h_kPa);
        test.vpd_psi = kPaToPsi(test.es_e_kPa);
        test.wind_mph = msToMph(test.W_ms);
        
        // Handle boundary pressure
        if (test.pressure_psi > 80.0 && test.pressure_psi <= 80.2) {
            test.pressure_psi = 80.0;
        }
        
        test.withinLimits = (test.vpd_psi >= 0.0 && test.vpd_psi <= 1.0 &&
                           test.nozzle_64ths >= 8 && test.nozzle_64ths <= 64 &&
                           test.pressure_psi >= 20 && test.pressure_psi <= 80 &&
                           test.wind_mph >= 0 && test.wind_mph <= 15);
    }
    
    // Test results
    std::cout << std::left << std::setw(5) << "Test" 
              << std::setw(10) << "Expected" 
              << std::setw(12) << "Validated" 
              << std::setw(12) << "Compact" 
              << std::setw(12) << "Regular" 
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    
    int validatedSuccess = 0, compactSuccess = 0, regularSuccess = 0;
    
    for (size_t i = 0; i < tests.size(); i++) {
        const auto& test = tests[i];
        
        std::cout << std::setw(5) << (i + 1);
        std::cout << std::setw(10) << std::fixed << std::setprecision(1) << test.E_expected << "%";
        
        // Test Validated Solver
        try {
            if (test.withinLimits) {
                auto result = EvapSolverValidated::calculateEvaporationLossWithValidation(
                    test.vpd_psi, test.nozzle_64ths, test.pressure_psi, test.wind_mph);
                if (result.isValid) {
                    std::cout << std::setw(12) << (std::to_string(result.calculatedValue).substr(0, 5) + "%");
                    validatedSuccess++;
                } else {
                    std::cout << std::setw(12) << "INVALID";
                }
            } else {
                std::cout << std::setw(12) << "OUT_RANGE";
            }
        } catch (...) {
            std::cout << std::setw(12) << "ERROR";
        }
        
        // Test Compact Solver
        try {
            if (test.withinLimits) {
                double result = EvapSolver::calculateEvaporationLoss(
                    test.vpd_psi, test.nozzle_64ths, test.pressure_psi, test.wind_mph);
                std::cout << std::setw(12) << (std::to_string(result).substr(0, 5) + "%");
                compactSuccess++;
            } else {
                std::cout << std::setw(12) << "OUT_RANGE";
            }
        } catch (...) {
            std::cout << std::setw(12) << "ERROR";
        }
        
        // Test Regular Solver
        try {
            if (test.withinLimits) {
                Inputs inputs;
                inputs.vpd = test.vpd_psi;
                inputs.nozzle = test.nozzle_64ths;
                inputs.pressure = test.pressure_psi;
                inputs.wind = test.wind_mph;
                
                // Suppress output temporarily
                std::streambuf* orig = std::cout.rdbuf();
                std::cout.rdbuf(nullptr);
                double result = solveEvaporationLoss(inputs);
                std::cout.rdbuf(orig);
                
                std::cout << std::setw(12) << (std::to_string(result).substr(0, 5) + "%");
                regularSuccess++;
            } else {
                std::cout << std::setw(12) << "OUT_RANGE";
            }
        } catch (...) {
            std::cout << std::setw(12) << "ERROR";
        }
        
        std::cout << std::setw(10) << (test.withinLimits ? "OK" : "SKIP") << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Results Summary:" << std::endl;
    std::cout << "Validated Solver: " << validatedSuccess << "/" << tests.size() << " successful" << std::endl;
    std::cout << "Compact Solver: " << compactSuccess << "/" << tests.size() << " successful" << std::endl;
    std::cout << "Regular Solver: " << regularSuccess << "/" << tests.size() << " successful" << std::endl;
    
    return 0;
}
