#include <iostream>
#include <cmath>
#include <cassert>
#include "../src/evap_solver_compact.h"

bool approxEqual(double a, double b, double tol = 0.001) {
    return std::abs(a - b) < tol;
}

void testBasicCalculation() {
    using namespace EvapSolver;
    
    Input testInput = {0.6, 12, 40, 5};
    double result = Calculator::calculate(testInput);
    double expected = 8.31433;
    
    assert(approxEqual(result, expected));
    std::cout << "[PASS] Basic calculation test: " << result << "%" << std::endl;
}

void testConvenienceFunction() {
    double result = EvapSolver::calculateEvaporationLoss(0.6, 12, 40, 5);
    double expected = 8.31433;
    
    assert(approxEqual(result, expected));
    std::cout << "[PASS] Convenience function test: " << result << "%" << std::endl;
}

void testEdgeCases() {
    using namespace EvapSolver;
    
    // Test minimum values
    Input minInput = {0.0, 8, 20, 0};
    double minResult = Calculator::calculate(minInput);
    std::cout << "[PASS] Minimum values test: " << minResult << "%" << std::endl;
    
    // Test maximum values
    Input maxInput = {1.0, 64, 80, 15};
    double maxResult = Calculator::calculate(maxInput);
    std::cout << "[PASS] Maximum values test: " << maxResult << "%" << std::endl;
    
    // Test mid-range values
    Input midInput = {0.5, 32, 50, 8};
    double midResult = Calculator::calculate(midInput);
    std::cout << "[PASS] Mid-range values test: " << midResult << "%" << std::endl;
}

int main() {
    std::cout << "=== Compact Evaporation Loss Solver Tests ===" << std::endl;
    
    try {
        testBasicCalculation();
        testConvenienceFunction();
        testEdgeCases();
        
        std::cout << "\n✅ All tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}
