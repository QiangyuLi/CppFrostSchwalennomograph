#include <iostream>
#include <cmath>
#include "../src/solver.h"  // Include header file instead of main.cpp

bool approxEqual(double a, double b, double tol = 0.1) {
    return std::abs(a - b) < tol;
}

int main() {
    Inputs testInput;
    testInput.vpd = 0.6;
    testInput.nozzle = 12;
    testInput.pressure = 40;
    testInput.wind = 5;

    double result = solveEvaporationLoss(testInput);
    double expected = 8.31433; // correct expected value

    if (approxEqual(result, expected)) {
        std::cout << "[PASS] Evaporation loss test passed: " << result << "%\n";
        return 0;
    } else {
        std::cerr << "[FAIL] Expected " << expected << "% but got " << result << "%\n";
        return 1;
    }
}
