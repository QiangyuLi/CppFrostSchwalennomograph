# Evaporation Loss Solver (C++ Version)

This project provides C++ implementations of the Frost & Schwalen nomograph method for estimating evaporation loss during sprinkler irrigation.

**Two implementations are provided:**
- **Full version**: Traditional multi-file structure with separate header and implementation
- **Compact version**: Single-header library for easy integration into other projects

Both perform the same calculation by:

* Interpolating vapor pressure deficit, nozzle diameter, pressure, and wind velocity values.
* Computing geometric pivot points based on nomograph layout.
* Intersecting these lines to determine percent evaporation loss.

---

## ✅ Features

* **Pure C++ implementation** - Uses standard library only
* **Header-only compact version** - Easy integration, no linking required
* **Built-in interpolation logic** - No external dependencies
* **Comprehensive test suite** - Both versions thoroughly tested
* **Simple API** - Easy to use in existing projects

---

## 🚀 Quick Start (Compact Version)

For easy integration into your project, use the compact single-header version:

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
1. Copy `src/evap_solver_compact.h` to your project
2. Include the header in your source files
3. Compile with C++17 standard: `g++ -std=c++17 your_file.cpp`

📖 **See [INTEGRATION.md](INTEGRATION.md) for detailed integration guide and examples.**

---

## 🔧 Build Instructions

### Full Version

Make sure you have a C++ compiler installed (like `g++`):

```bash
g++ -std=c++17 -o evap_solver src/main.cpp src/solver.cpp
```

Then run:

```bash
./evap_solver
```

### Compact Version Example

```bash
g++ -std=c++17 -o compact_example examples/compact_example.cpp
./compact_example
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

## 📋 API Reference (Compact Version)

### Namespace: `EvapSolver`

#### Input Structure
```cpp
struct Input {
    double vpd;      // Vapor-Pressure Deficit (psi)
    int nozzle;      // Nozzle diameter (64ths inch)  
    double pressure; // Pressure (psi)
    double wind;     // Wind velocity (mph)
};
```

#### Calculator Class
```cpp
class Calculator {
public:
    static double calculate(const Input& in);
};
```

#### Convenience Function
```cpp
double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind);
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
