#include <iostream>
#include <vector>
#include "../src/evap_solver_validated.h"
#include "../src/evap_solver_compact.h"
#include "../src/solver.h"

int main() {
    std::cout << "Starting multi-solver validation test..." << std::endl;
    
    // Test basic functionality
    try {
        std::cout << "Testing Validated Solver..." << std::endl;
        auto result = EvapSolverValidated::calculateEvaporationLossWithValidation(0.5, 12, 40, 5);
        std::cout << "Validated result: " << result.calculatedValue << std::endl;
        
        std::cout << "Testing Compact Solver..." << std::endl;
        double compactResult = EvapSolver::calculateEvaporationLoss(0.5, 12, 40, 5);
        std::cout << "Compact result: " << compactResult << std::endl;
        
        std::cout << "Testing Regular Solver..." << std::endl;
        Inputs inputs;
        inputs.vpd = 0.5;
        inputs.nozzle = 12;
        inputs.pressure = 40;
        inputs.wind = 5;
        
        // Capture stdout to suppress output
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(nullptr);
        double regularResult = solveEvaporationLoss(inputs);
        std::cout.rdbuf(orig);
        
        std::cout << "Regular result: " << regularResult << std::endl;
        
        std::cout << "All solvers working!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
