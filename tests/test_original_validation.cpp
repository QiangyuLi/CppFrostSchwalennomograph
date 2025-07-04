#include <iostream>
#include <cmath>
#include "../src/solver.h"

bool approxEqual(double a, double b, double tol = 0.1) {
    return std::abs(a - b) < tol;
}

int main() {
    std::cout << "=== Testing Original Solver with Validation ===" << std::endl;
    
    // Test valid input
    std::cout << "Testing valid input:" << std::endl;
    Inputs validInput;
    validInput.vpd = 0.6;
    validInput.nozzle = 12;
    validInput.pressure = 40;
    validInput.wind = 5;
    
    try {
        double result = solveEvaporationLoss(validInput);
        std::cout << "✅ Valid input test passed: " << result << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "❌ Unexpected error: " << e.what() << std::endl;
    }
    
    // Test invalid inputs
    std::cout << "\nTesting invalid inputs:" << std::endl;
    
    // Test invalid VPD
    std::cout << "Testing invalid VPD (-0.1):" << std::endl;
    Inputs invalidVPD;
    invalidVPD.vpd = -0.1;
    invalidVPD.nozzle = 12;
    invalidVPD.pressure = 40;
    invalidVPD.wind = 5;
    
    try {
        double result = solveEvaporationLoss(invalidVPD);
        std::cout << "❌ Expected error but got result: " << result << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✅ Correctly caught error: " << e.what() << std::endl;
    }
    
    // Test invalid nozzle
    std::cout << "Testing invalid nozzle (5):" << std::endl;
    Inputs invalidNozzle;
    invalidNozzle.vpd = 0.6;
    invalidNozzle.nozzle = 5;
    invalidNozzle.pressure = 40;
    invalidNozzle.wind = 5;
    
    try {
        double result = solveEvaporationLoss(invalidNozzle);
        std::cout << "❌ Expected error but got result: " << result << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✅ Correctly caught error: " << e.what() << std::endl;
    }
    
    return 0;
}
