#include <iostream>
#include <cmath>
#include <cassert>
#include "../src/evap_solver_validated.h"

bool approxEqual(double a, double b, double tol = 0.001) {
    return std::abs(a - b) < tol;
}

void testValidInputs() {
    std::cout << "=== Testing Valid Inputs ===" << std::endl;
    
    using namespace EvapSolverValidated;
    
    // Test normal case
    Input validInput(0.6, 12, 40, 5);
    double result = Calculator::calculate(validInput);
    assert(approxEqual(result, 8.31433));
    std::cout << "[PASS] Valid input test: " << result << "%" << std::endl;
    
    // Test with validation result
    ValidationResult valResult = Calculator::calculateWithValidation(validInput);
    assert(valResult.isValid);
    assert(approxEqual(valResult.calculatedValue, 8.31433));
    assert(!valResult.isOutOfRange);
    std::cout << "[PASS] Validation result test: " << valResult.calculatedValue << "%" << std::endl;
    
    // Test convenience function
    double convResult = calculateEvaporationLoss(0.6, 12, 40, 5);
    assert(approxEqual(convResult, 8.31433));
    std::cout << "[PASS] Convenience function test: " << convResult << "%" << std::endl;
}

void testInvalidInputs() {
    std::cout << "\n=== Testing Invalid Inputs ===" << std::endl;
    
    using namespace EvapSolverValidated;
    
    struct InvalidCase {
        double vpd, pressure, wind;
        int nozzle;
        std::string description;
    };
    
    InvalidCase cases[] = {
        {-0.1, 12, 40, 5, "Negative VPD"},
        {1.5, 12, 40, 5, "VPD too high"},
        {0.6, 5, 40, 5, "Nozzle too small"},
        {0.6, 100, 40, 5, "Nozzle too large"},
        {0.6, 12, 10, 5, "Pressure too low"},
        {0.6, 12, 100, 5, "Pressure too high"},
        {0.6, 12, 40, -1, "Negative wind"},
        {0.6, 12, 40, 20, "Wind too high"}
    };
    
    for (const auto& testCase : cases) {
        ValidationResult result = calculateEvaporationLossWithValidation(
            testCase.vpd, testCase.nozzle, testCase.pressure, testCase.wind);
        
        assert(!result.isValid);
        std::cout << "[PASS] " << testCase.description << " - Error: " 
                  << result.errorMessage << std::endl;
    }
}

void testBoundaryValues() {
    std::cout << "\n=== Testing Boundary Values ===" << std::endl;
    
    using namespace EvapSolverValidated;
    
    struct BoundaryCase {
        double vpd, pressure, wind;
        int nozzle;
        std::string description;
    };
    
    BoundaryCase cases[] = {
        {0.0, 20, 0, 8, "All minimum values"},
        {1.0, 80, 15, 64, "All maximum values"},
        {0.5, 50, 7, 32, "All middle values"}
    };
    
    for (const auto& testCase : cases) {
        ValidationResult result = calculateEvaporationLossWithValidation(
            testCase.vpd, testCase.nozzle, testCase.pressure, testCase.wind);
        
        assert(result.isValid);
        std::cout << "[PASS] " << testCase.description << " - Result: " 
                  << result.calculatedValue << "%" << std::endl;
        
        if (result.isOutOfRange) {
            std::cout << "  [WARNING] Result is outside expected range (0-40%)" << std::endl;
        }
    }
}

void testSafeFunction() {
    std::cout << "\n=== Testing Safe Function ===" << std::endl;
    
    using namespace EvapSolverValidated;
    
    // Test with valid input
    double result1 = calculateEvaporationLossSafe(0.6, 12, 40, 5, -1.0);
    assert(approxEqual(result1, 8.31433));
    std::cout << "[PASS] Safe function with valid input: " << result1 << "%" << std::endl;
    
    // Test with invalid input
    double result2 = calculateEvaporationLossSafe(-0.5, 12, 40, 5, -1.0);
    assert(result2 == -1.0);
    std::cout << "[PASS] Safe function with invalid input returned default: " << result2 << std::endl;
}

void testParameterRanges() {
    std::cout << "\n=== Parameter Ranges ===" << std::endl;
    std::cout << EvapSolverValidated::Calculator::getParameterRanges() << std::endl;
}

void testExceptionHandling() {
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    
    using namespace EvapSolverValidated;
    
    try {
        Input invalidInput(-0.1, 12, 40, 5);
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        std::cout << "[PASS] Constructor validation caught: " << e.what() << std::endl;
    }
    
    try {
        calculateEvaporationLoss(0.6, 5, 40, 5);
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        std::cout << "[PASS] Function validation caught: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Validated Evaporation Loss Solver Tests ===" << std::endl;
    
    try {
        testValidInputs();
        testInvalidInputs();
        testBoundaryValues();
        testSafeFunction();
        testParameterRanges();
        testExceptionHandling();
        
        std::cout << "\n✅ All validation tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}
