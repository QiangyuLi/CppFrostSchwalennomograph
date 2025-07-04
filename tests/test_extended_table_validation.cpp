#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <iomanip>
#include "../src/evap_solver_compact.h"

bool approxEqual(double a, double b, double tol = 1.0) {
    return std::abs(a - b) <= tol;
}

// Conversion functions from metric to imperial units
double mmToSixtyFourthsInch(double mm) {
    return mm / 25.4 * 64.0;
}

double kPaToPsi(double kPa) {
    return kPa * 0.145038;
}

double msToMph(double ms) {
    return ms * 2.237;
}

void testTableDataWithCompactSolver() {
    std::cout << "=== Compact Solver Table Validation ===" << std::endl;
    std::cout << "Testing compact solver against validation table data" << std::endl;
    std::cout << std::endl;
    
    // Test cases from the table that should work with compact solver
    struct TestCase {
        double D_mm, h_kPa, es_e_kPa, W_ms, expected;
        std::string description;
    };
    
    std::vector<TestCase> testCases = {
        // Cases within solver limits
        {3.18, 207, 2.8, 1.3, 5.5, "Small nozzle, low pressure, low VPD, low wind"},
        {3.18, 207, 4.5, 4.5, 16.0, "Small nozzle, low pressure, high VPD, high wind"},
        {4.76, 207, 4.5, 4.5, 10.0, "Medium nozzle, low pressure, high VPD, high wind"},
        {4.76, 414, 4.5, 2.2, 13.0, "Medium nozzle, medium pressure, high VPD, medium wind"},
        {4.76, 414, 2.8, 1.3, 7.0, "Medium nozzle, medium pressure, low VPD, low wind"},
        {4.76, 414, 2.8, 4.5, 14.0, "Medium nozzle, medium pressure, low VPD, high wind"},
        {6.35, 414, 2.8, 4.5, 11.0, "Large nozzle, medium pressure, low VPD, high wind"},
        {6.35, 414, 4.5, 2.7, 9.5, "Large nozzle, medium pressure, high VPD, medium wind"},
        {6.35, 414, 4.5, 1.3, 7.5, "Large nozzle, medium pressure, high VPD, low wind"},
        // Note: Higher pressure cases (552 kPa = 80.1 psi) are at the edge of solver limits
    };
    
    std::cout << std::fixed << std::setprecision(2);
    
    int passCount = 0;
    int totalCount = 0;
    
    for (const auto& test : testCases) {
        totalCount++;
        
        // Convert units
        double nozzle_exact = mmToSixtyFourthsInch(test.D_mm);
        int nozzle_64ths = static_cast<int>(std::round(nozzle_exact));
        double pressure_psi = kPaToPsi(test.h_kPa);
        double vpd_psi = kPaToPsi(test.es_e_kPa);
        double wind_mph = msToMph(test.W_ms);
        
        std::cout << "Test: " << test.description << std::endl;
        std::cout << "  Metric: D=" << test.D_mm << "mm, h=" << test.h_kPa 
                  << "kPa, es-e=" << test.es_e_kPa << "kPa, W=" << test.W_ms << "m/s" << std::endl;
        std::cout << "  Imperial: Nozzle=" << nozzle_64ths << "/64\", Pressure=" 
                  << pressure_psi << "psi, VPD=" << vpd_psi << "psi, Wind=" << wind_mph << "mph" << std::endl;
        
        // Check if within solver limits
        bool withinLimits = (vpd_psi >= 0.0 && vpd_psi <= 1.0) &&
                           (nozzle_64ths >= 8 && nozzle_64ths <= 64) &&
                           (pressure_psi >= 20 && pressure_psi <= 80) &&
                           (wind_mph >= 0 && wind_mph <= 15);
        
        if (!withinLimits) {
            std::cout << "  ⚠️  Parameters outside solver limits - skipping" << std::endl;
            std::cout << std::endl;
            continue;
        }
        
        // Calculate using compact solver
        double calculated = EvapSolver::calculateEvaporationLoss(
            vpd_psi, nozzle_64ths, pressure_psi, wind_mph);
        
        std::cout << "  Expected: " << test.expected << "%" << std::endl;
        std::cout << "  Calculated: " << calculated << "%" << std::endl;
        
        double difference = std::abs(calculated - test.expected);
        double percentDiff = (difference / test.expected) * 100.0;
        
        std::cout << "  Difference: " << difference << "% (±" << percentDiff << "%)" << std::endl;
        
        if (approxEqual(calculated, test.expected, 3.0)) {
            std::cout << "  ✅ PASS" << std::endl;
            passCount++;
        } else {
            std::cout << "  ❌ FAIL" << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "Results: " << passCount << "/" << totalCount << " tests passed" << std::endl;
    std::cout << std::endl;
}

void testExtremeCases() {
    std::cout << "=== Extreme Case Testing ===" << std::endl;
    std::cout << "Testing edge cases and extreme parameter combinations" << std::endl;
    std::cout << std::endl;
    
    struct ExtremeCase {
        double vpd, pressure, wind;
        int nozzle;
        std::string description;
    };
    
    std::vector<ExtremeCase> extremeCases = {
        // Edge cases at solver limits
        {0.0, 20, 0, 8, "Minimum all parameters"},
        {1.0, 80, 15, 64, "Maximum all parameters"},
        {0.5, 50, 7.5, 32, "Mid-range all parameters"},
        
        // High evaporation scenarios
        {1.0, 20, 15, 8, "High VPD, low pressure, high wind, small nozzle"},
        {0.9, 25, 12, 10, "High VPD, low pressure, high wind, small nozzle"},
        
        // Low evaporation scenarios
        {0.1, 80, 1, 64, "Low VPD, high pressure, low wind, large nozzle"},
        {0.2, 70, 2, 48, "Low VPD, high pressure, low wind, large nozzle"},
        
        // Mixed scenarios
        {0.7, 40, 10, 16, "Medium-high VPD, medium pressure, high wind, medium nozzle"},
        {0.3, 60, 5, 24, "Low VPD, high pressure, medium wind, large nozzle"},
    };
    
    std::cout << std::fixed << std::setprecision(2);
    
    for (const auto& test : extremeCases) {
        std::cout << "Test: " << test.description << std::endl;
        std::cout << "  Input: VPD=" << test.vpd << "psi, Nozzle=" << test.nozzle 
                  << "/64\", Pressure=" << test.pressure << "psi, Wind=" << test.wind << "mph" << std::endl;
        
        double result = EvapSolver::calculateEvaporationLoss(
            test.vpd, test.nozzle, test.pressure, test.wind);
        
        std::cout << "  Result: " << result << "%" << std::endl;
        
        // Check if result is reasonable (0-40% range)
        if (result >= 0 && result <= 40) {
            std::cout << "  ✅ Result within expected range" << std::endl;
        } else {
            std::cout << "  ⚠️  Result outside expected range (0-40%)" << std::endl;
        }
        
        std::cout << std::endl;
    }
}

void testParameterSensitivity() {
    std::cout << "=== Parameter Sensitivity Analysis ===" << std::endl;
    std::cout << "Testing how changes in each parameter affect the result" << std::endl;
    std::cout << std::endl;
    
    // Base case
    double base_vpd = 0.5, base_pressure = 40, base_wind = 5;
    int base_nozzle = 16;
    
    double base_result = EvapSolver::calculateEvaporationLoss(
        base_vpd, base_nozzle, base_pressure, base_wind);
    
    std::cout << "Base case: VPD=" << base_vpd << "psi, Nozzle=" << base_nozzle 
              << "/64\", Pressure=" << base_pressure << "psi, Wind=" << base_wind << "mph" << std::endl;
    std::cout << "Base result: " << std::fixed << std::setprecision(2) << base_result << "%" << std::endl;
    std::cout << std::endl;
    
    // VPD sensitivity
    std::cout << "VPD Sensitivity:" << std::endl;
    for (double vpd = 0.1; vpd <= 1.0; vpd += 0.2) {
        double result = EvapSolver::calculateEvaporationLoss(
            vpd, base_nozzle, base_pressure, base_wind);
        double change = result - base_result;
        std::cout << "  VPD=" << vpd << "psi: " << result << "% (change: " 
                  << std::showpos << change << std::noshowpos << "%)" << std::endl;
    }
    std::cout << std::endl;
    
    // Pressure sensitivity
    std::cout << "Pressure Sensitivity:" << std::endl;
    for (double pressure = 20; pressure <= 80; pressure += 15) {
        double result = EvapSolver::calculateEvaporationLoss(
            base_vpd, base_nozzle, pressure, base_wind);
        double change = result - base_result;
        std::cout << "  Pressure=" << pressure << "psi: " << result << "% (change: " 
                  << std::showpos << change << std::noshowpos << "%)" << std::endl;
    }
    std::cout << std::endl;
    
    // Wind sensitivity
    std::cout << "Wind Sensitivity:" << std::endl;
    for (double wind = 0; wind <= 15; wind += 3) {
        double result = EvapSolver::calculateEvaporationLoss(
            base_vpd, base_nozzle, base_pressure, wind);
        double change = result - base_result;
        std::cout << "  Wind=" << wind << "mph: " << result << "% (change: " 
                  << std::showpos << change << std::noshowpos << "%)" << std::endl;
    }
    std::cout << std::endl;
    
    // Nozzle sensitivity
    std::cout << "Nozzle Sensitivity:" << std::endl;
    for (int nozzle = 8; nozzle <= 64; nozzle += 12) {
        double result = EvapSolver::calculateEvaporationLoss(
            base_vpd, nozzle, base_pressure, base_wind);
        double change = result - base_result;
        std::cout << "  Nozzle=" << nozzle << "/64\": " << result << "% (change: " 
                  << std::showpos << change << std::noshowpos << "%)" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Extended Table Validation Test Suite ===" << std::endl;
    std::cout << "Testing compact solver with extended validation scenarios" << std::endl;
    std::cout << std::endl;
    
    try {
        testTableDataWithCompactSolver();
        testExtremeCases();
        testParameterSensitivity();
        
        std::cout << "✅ All extended table validation tests completed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}
