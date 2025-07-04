#include <iostream>
#include "../src/evap_solver_compact.h"

int main() {
    std::cout << "=== Compact Evaporation Loss Calculator ===" << std::endl;
    
    // Method 1: Using the convenience function
    double loss1 = EvapSolver::calculateEvaporationLoss(0.6, 12, 40, 5);
    std::cout << "Method 1 - Convenience function: " << loss1 << "%" << std::endl;
    
    // Method 2: Using the Calculator class
    EvapSolver::Input input = {0.6, 12, 40, 5};
    double loss2 = EvapSolver::Calculator::calculate(input);
    std::cout << "Method 2 - Calculator class: " << loss2 << "%" << std::endl;
    
    // Example with different parameters
    std::cout << "\n=== Different Parameter Examples ===" << std::endl;
    
    struct TestCase {
        double vpd, pressure, wind;
        int nozzle;
        const char* description;
    };
    
    TestCase testCases[] = {
        {0.3, 12, 30, 3, "Low VPD, low pressure, low wind"},
        {0.8, 16, 60, 8, "High VPD, high pressure, high wind"},
        {0.5, 20, 45, 6, "Medium conditions"},
        {0.6, 32, 40, 10, "Large nozzle, high wind"}
    };
    
    for (const auto& test : testCases) {
        double result = EvapSolver::calculateEvaporationLoss(test.vpd, test.nozzle, test.pressure, test.wind);
        std::cout << test.description << ": " << result << "%" << std::endl;
    }
    
    return 0;
}
