# Integration Guide - Compact Evaporation Loss Solver

## Overview
The compact evaporation loss solver is a single-header C++ library that calculates evaporation loss during sprinkler irrigation using the Frost & Schwalen nomograph method.

## Quick Integration

### Step 1: Copy the Header
Copy `src/evap_solver_compact.h` to your project directory.

### Step 2: Include in Your Code
```cpp
#include "evap_solver_compact.h"
```

### Step 3: Use the API
```cpp
#include <iostream>
#include "evap_solver_compact.h"

int main() {
    // Simple calculation
    double loss = EvapSolver::calculateEvaporationLoss(0.6, 12, 40, 5);
    std::cout << "Evaporation Loss: " << loss << "%" << std::endl;
    
    return 0;
}
```

### Step 4: Compile
```bash
g++ -std=c++17 -o your_program your_program.cpp
```

## API Reference

### Input Parameters
- `vpd`: Vapor-Pressure Deficit (psi) - Range: 0.0 to 1.0
- `nozzle`: Nozzle diameter (64ths inch) - Range: 8 to 64
- `pressure`: Pressure (psi) - Range: 20 to 80
- `wind`: Wind velocity (mph) - Range: 0 to 15

### Methods

#### 1. Convenience Function (Recommended)
```cpp
double loss = EvapSolver::calculateEvaporationLoss(vpd, nozzle, pressure, wind);
```

#### 2. Calculator Class
```cpp
EvapSolver::Input input = {vpd, nozzle, pressure, wind};
double loss = EvapSolver::Calculator::calculate(input);
```

## Example Use Cases

### Agricultural Irrigation System
```cpp
// Calculate loss for different field conditions
double morning_loss = EvapSolver::calculateEvaporationLoss(0.3, 12, 40, 2);
double afternoon_loss = EvapSolver::calculateEvaporationLoss(0.8, 12, 40, 8);

if (afternoon_loss > 10.0) {
    std::cout << "High evaporation expected - consider morning irrigation" << std::endl;
}
```

### Sprinkler Design Tool
```cpp
// Compare different nozzle sizes
struct NozzleTest {
    int size;
    double loss;
};

std::vector<NozzleTest> results;
for (int nozzle = 8; nozzle <= 32; nozzle += 4) {
    double loss = EvapSolver::calculateEvaporationLoss(0.6, nozzle, 40, 5);
    results.push_back({nozzle, loss});
}

// Find optimal nozzle size
auto best = std::min_element(results.begin(), results.end(), 
    [](const NozzleTest& a, const NozzleTest& b) { return a.loss < b.loss; });
```

## Requirements
- C++17 compatible compiler (for structured bindings)
- Standard library only (no external dependencies)

## Thread Safety
The calculator is thread-safe for read-only operations. The static lookup tables are initialized once and then remain constant.

## Performance Notes
- First calculation initializes static lookup tables
- Subsequent calculations are very fast (mostly just interpolation)
- Memory usage is minimal (only the lookup tables)

## Error Handling
The calculator will throw `std::runtime_error` if:
- Empty interpolation tables are provided (internal error)
- Invalid input parameters outside expected ranges may produce unexpected results

## Validation
The solver has been tested against the original MATLAB implementation and produces identical results within numerical precision limits.
