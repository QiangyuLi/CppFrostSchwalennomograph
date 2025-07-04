#include <iostream>
#include <iomanip>
#include "../src/evap_solver_validated.h"

void demonstrateValidatedSolver() {
    std::cout << "=== Validated Evaporation Loss Calculator Demo ===" << std::endl;
    std::cout << std::endl;
    
    // Show parameter ranges
    std::cout << EvapSolverValidated::Calculator::getParameterRanges() << std::endl;
    std::cout << std::endl;
    
    // Test valid inputs
    std::cout << "=== Valid Input Examples ===" << std::endl;
    
    struct TestCase {
        double vpd, pressure, wind;
        int nozzle;
        std::string description;
    };
    
    TestCase validCases[] = {
        {0.6, 40, 5, 12, "Standard conditions"},
        {0.2, 20, 0, 8, "Low evaporation conditions"},
        {0.9, 70, 12, 32, "High evaporation conditions"},
        {0.5, 50, 8, 20, "Medium conditions"}
    };
    
    std::cout << std::fixed << std::setprecision(2);
    
    for (const auto& test : validCases) {
        auto result = EvapSolverValidated::calculateEvaporationLossWithValidation(
            test.vpd, test.nozzle, test.pressure, test.wind);
        
        std::cout << "• " << test.description << std::endl;
        std::cout << "  Input: VPD=" << test.vpd << ", Nozzle=" << test.nozzle 
                  << ", Pressure=" << test.pressure << ", Wind=" << test.wind << std::endl;
        std::cout << "  Result: " << result.calculatedValue << "%" << std::endl;
        
        if (result.isOutOfRange) {
            std::cout << "  ⚠️  WARNING: Result outside expected range (0-40%)" << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Test invalid inputs
    std::cout << "=== Invalid Input Examples ===" << std::endl;
    
    TestCase invalidCases[] = {
        {-0.1, 40, 5, 12, "Negative VPD"},
        {1.5, 40, 5, 12, "VPD too high"},
        {0.6, 40, 5, 5, "Nozzle too small"},
        {0.6, 15, 5, 12, "Pressure too low"},
        {0.6, 40, 20, 12, "Wind too high"}
    };
    
    for (const auto& test : invalidCases) {
        auto result = EvapSolverValidated::calculateEvaporationLossWithValidation(
            test.vpd, test.nozzle, test.pressure, test.wind);
        
        std::cout << "• " << test.description << std::endl;
        std::cout << "  Input: VPD=" << test.vpd << ", Nozzle=" << test.nozzle 
                  << ", Pressure=" << test.pressure << ", Wind=" << test.wind << std::endl;
        std::cout << "  ❌ Error: " << result.errorMessage << std::endl;
        std::cout << std::endl;
    }
}

void demonstrateUsageMethods() {
    std::cout << "=== Different Usage Methods ===" << std::endl;
    
    // Method 1: Direct function call (throws on error)
    std::cout << "1. Direct function call:" << std::endl;
    try {
        double result = EvapSolverValidated::calculateEvaporationLoss(0.6, 12, 40, 5);
        std::cout << "   Result: " << result << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "   Error: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    
    // Method 2: Validation result (no exceptions)
    std::cout << "2. Validation result method:" << std::endl;
    auto valResult = EvapSolverValidated::calculateEvaporationLossWithValidation(0.6, 12, 40, 5);
    if (valResult.isValid) {
        std::cout << "   Result: " << valResult.calculatedValue << "%" << std::endl;
    } else {
        std::cout << "   Error: " << valResult.errorMessage << std::endl;
    }
    std::cout << std::endl;
    
    // Method 3: Safe function (returns default on error)
    std::cout << "3. Safe function method:" << std::endl;
    double safeResult = EvapSolverValidated::calculateEvaporationLossSafe(0.6, 12, 40, 5, -1.0);
    std::cout << "   Result: " << safeResult << "%" << std::endl;
    
    // Try with invalid input
    double safeInvalidResult = EvapSolverValidated::calculateEvaporationLossSafe(-0.1, 12, 40, 5, -1.0);
    std::cout << "   Invalid input result: " << safeInvalidResult << " (default value)" << std::endl;
    std::cout << std::endl;
    
    // Method 4: Using Input structure
    std::cout << "4. Input structure method:" << std::endl;
    try {
        EvapSolverValidated::Input input(0.6, 12, 40, 5);
        double structResult = EvapSolverValidated::Calculator::calculate(input);
        std::cout << "   Result: " << structResult << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "   Error: " << e.what() << std::endl;
    }
}

int main() {
    demonstrateValidatedSolver();
    std::cout << std::endl;
    demonstrateUsageMethods();
    
    return 0;
}
