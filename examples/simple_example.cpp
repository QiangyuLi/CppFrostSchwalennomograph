/*
 * Example usage of the ultra-minimal evaporation calculator
 * Just include the header and call the function!
 */

#include <iostream>
#include "evap_calculator.h"

int main() {
    std::cout << "=== Ultra-Minimal Evaporation Calculator Example ===" << std::endl;
    
    // Simple usage - just call the function
    double loss = calculateEvaporationLoss(0.6, 12, 40, 5);
    std::cout << "Evaporation loss: " << loss << "%" << std::endl;
    
    // Multiple examples
    std::cout << "\n=== More Examples ===" << std::endl;
    
    struct {
        double vpd;
        int nozzle;
        double pressure, wind;
        const char* description;
    } examples[] = {
        {0.3, 12, 30, 3, "Low conditions"},
        {0.8, 16, 60, 8, "High conditions"},
        {0.5, 20, 45, 6, "Medium conditions"},
        {0.6, 32, 40, 10, "Large nozzle"}
    };
    
    for (const auto& ex : examples) {
        double result = calculateEvaporationLoss(ex.vpd, ex.nozzle, ex.pressure, ex.wind);
        std::cout << ex.description << ": " << result << "%" << std::endl;
    }
    
    return 0;
}
