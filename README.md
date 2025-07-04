# Evaporation Loss Solver (C++ Version)

This project provides C++ implementations of the Frost & Schwalen nomograph method for estimating evaporation loss during sprinkler irrigation.

**Three implementations are provided:**
- **Full version**: Traditional multi-file structure with separate header and implementation  
- **Compact version**: Single-header library for easy integration into other projects
- **Validated version**: Single-header library with comprehensive input validation and error handling

All perform the same calculation by:

* Interpolating vapor pressure deficit, nozzle diameter, pressure, and wind velocity values.
* Computing geometric pivot points based on nomograph layout.
* Intersecting these lines to determine percent evaporation loss.

---

## ✅ Features

* **Pure C++ implementation** - Uses standard library only
* **Multiple integration options** - Choose the version that fits your needs
* **Input validation** - Ensures parameters are within physical limits
* **Built-in interpolation logic** - No external dependencies
* **Comprehensive test suite** - All versions thoroughly tested
* **Error handling** - Graceful handling of invalid inputs

---

## 📊 Physical Parameter Limits

All versions respect the following physical constraints:

| Parameter | Range | Units | Description |
|-----------|-------|-------|-------------|
| **VPD** | 0.0 to 1.0 | psi | Vapor-Pressure Deficit |
| **Nozzle** | 8 to 64 | 64ths inch | Nozzle diameter (8/64" to 64/64") |
| **Pressure** | 20 to 80 | psi | Nozzle pressure |
| **Wind** | 0 to 15 | mph | Wind velocity |
| **Output** | 0 to 40 | % | Expected evaporation loss range |

---

## 🚀 Quick Start

### Validated Version (Recommended)

For projects requiring robust input validation and error handling:

```cpp
#include "evap_solver_validated.h"
#include <iostream>

int main() {
    // Method 1: Safe calculation (returns default on error)
    double loss = EvapSolverValidated::calculateEvaporationLossSafe(0.6, 12, 40, 5, -1.0);
    if (loss >= 0) {
        std::cout << "Evaporation Loss: " << loss << "%" << std::endl;
    } else {
        std::cout << "Invalid input parameters" << std::endl;
    }
    
    // Method 2: Validation result (detailed error info)
    auto result = EvapSolverValidated::calculateEvaporationLossWithValidation(0.6, 12, 40, 5);
    if (result.isValid) {
        std::cout << "Evaporation Loss: " << result.calculatedValue << "%" << std::endl;
        if (result.isOutOfRange) {
            std::cout << "Warning: Result outside expected range (0-40%)" << std::endl;
        }
    } else {
        std::cout << "Error: " << result.errorMessage << std::endl;
    }
    
    return 0;
}
```

### Compact Version (Fast Integration)

For quick integration into existing projects:

```cpp
#include "evap_solver_compact.h"
#include <iostream>

int main() {
    // Method 1: Convenience function
    double loss = EvapSolver::calculateEvaporationLoss(0.6, 12, 40, 5);
    std::cout << "Evaporation Loss: " << loss << "%" << std::endl;
    
    // Method 2: Using Input struct
    EvapSolver::Input input = {0.6, 12, 40, 5};
    double loss2 = EvapSolver::Calculator::calculate(input);
    std::cout << "Evaporation Loss: " << loss2 << "%" << std::endl;
    
    return 0;
}
```

**Integration steps:**
1. Copy the appropriate header file to your project
2. Include the header in your source files  
3. Compile with C++17 standard: `g++ -std=c++17 your_file.cpp`

📖 **See [INTEGRATION.md](INTEGRATION.md) for detailed integration guide and examples.**

---

## 🔧 Build Instructions

### Full Version

```bash
g++ -std=c++17 -o evap_solver src/main.cpp src/solver.cpp
./evap_solver
```

### Compact Version Example

```bash
g++ -std=c++17 -o compact_example examples/compact_example.cpp
./compact_example
```

### Validated Version Example

```bash
g++ -std=c++17 -o validated_example examples/validated_example.cpp
./validated_example
```

---

## 📄 Example Output

```
Evaporation Loss: 8.31433%
```

---

## 🧪 Running Tests

To build and run the complete test suite:

```bash
cd tests
./run_tests.sh
```

This will test both the full and compact versions.

---

## 📋 API Reference

### Validated Version (evap_solver_validated.h)

**Recommended for production use**

```cpp
namespace EvapSolverValidated {
    // Input with validation
    struct Input {
        double vpd, pressure, wind;
        int nozzle;
        Input(double vpd, int nozzle, double pressure, double wind); // Validates on construction
    };
    
    // Validation result
    struct ValidationResult {
        bool isValid;
        std::string errorMessage;
        double calculatedValue;
        bool isOutOfRange;
    };
    
    // Calculator class
    class Calculator {
    public:
        static ValidationResult calculateWithValidation(const Input& in);
        static double calculate(const Input& in); // Throws on invalid input
        static std::string getParameterRanges();
    };
    
    // Convenience functions
    ValidationResult calculateEvaporationLossWithValidation(double vpd, int nozzle, double pressure, double wind);
    double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind);
    double calculateEvaporationLossSafe(double vpd, int nozzle, double pressure, double wind, double defaultValue);
}
```

### Compact Version (evap_solver_compact.h)

**For quick integration**

```cpp
namespace EvapSolver {
    struct Input {
        double vpd, pressure, wind;
        int nozzle;
    };
    
    class Calculator {
    public:
        static double calculate(const Input& in);
    };
    
    double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind);
}
```

### Full Version (solver.h + solver.cpp)

**Traditional multi-file approach**

```cpp
struct Inputs {
    double vpd, pressure, wind;
    int nozzle;
};

double solveEvaporationLoss(const Inputs& in);
```

---

---

## 📄 Example Output

```
Evaporation Loss: 8.31433%
```

---

## ⚙️ Input Parameters

Modify the `Inputs` struct in `main()` to set your own conditions:

```cpp
Inputs inputs;
inputs.vpd = 0.6;        // Vapor-Pressure Deficit (psi)
inputs.nozzle = 12;      // Nozzle diameter (64ths inch)
inputs.pressure = 40;    // Pressure (psi)
inputs.wind = 5;         // Wind velocity (mph)
```

---

## 📚 Reference

Frost, K. R., & Schwalen, H. C. (1960). *Evapotranspiration during sprinkler irrigation.*
Transactions of the ASAE, 3(1), 18–20.
[https://doi.org/10.13031/2013.41072](https://doi.org/10.13031/2013.41072)

---

## ⚠️ Disclaimer

This software is provided **"as is"** without warranties. Use at your own risk.
