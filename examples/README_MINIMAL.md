# Minimal Evaporation Loss Calculator

**📅 Updated: July 2025**

Ultra-lightweight implementations of the evaporation loss calculator for fast integration into any C++ project.

## 🆕 What's New
- **Ultra-minimal versions** created for instant integration
- **Header-only design** - single file, no compilation needed
- **Copy-paste ready** - function can be directly copied
- **Zero namespace pollution** - uses only std library
- **30-second integration** - fastest possible setup
- **Consistent results** - all versions produce identical output

## Files

### 1. `evap_calculator.h` - Header-Only Version (RECOMMENDED)
- **Single header file** - just copy and include
- **No custom namespaces** - uses std namespace only
- **No dependencies** except standard library
- **Smallest footprint** for easy integration

### 2. `minimal_evap_calculator.cpp` - Standalone Version
- Complete standalone program
- Shows example usage
- Can be compiled and run independently

### 3. `simple_example.cpp` - Usage Example
- Demonstrates how to use the header-only version
- Clean, simple example code

## Quick Start

### Option 1: Header-Only (Easiest)
```cpp
#include "evap_calculator.h"
#include <iostream>

int main() {
    double loss = calculateEvaporationLoss(0.6, 12, 40, 5);
    std::cout << "Evaporation loss: " << loss << "%" << std::endl;
    return 0;
}
```

### Option 2: Copy Function Directly
Just copy the `calculateEvaporationLoss` function from `evap_calculator.h` directly into your code.

## Function Signature
```cpp
double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind);
```

## Parameters
- `vpd`: Vapor-Pressure Deficit (psi)
- `nozzle`: Nozzle diameter (64ths inch)
- `pressure`: Pressure (psi)  
- `wind`: Wind velocity (mph)

## Returns
- Evaporation loss percentage (double)

## Compilation
```bash
g++ -o your_program your_program.cpp -std=c++17
```

## Integration Steps
1. Copy `evap_calculator.h` to your project
2. Include it: `#include "evap_calculator.h"`
3. Call the function: `calculateEvaporationLoss(vpd, nozzle, pressure, wind)`
4. Done!

## Example Output
```
Low conditions: 3.33%
Standard conditions: 8.31%
High conditions: 15.61%
```

## Features
- ✅ **NEW: Zero namespace pollution** - uses only std library
- ✅ **NEW: 30-second integration** - fastest possible setup
- ✅ **NEW: Copy-paste ready** - single function can be directly copied
- ✅ No external dependencies
- ✅ Header-only design
- ✅ Uses only std library
- ✅ No custom namespaces
- ✅ Fast compilation
- ✅ Easy integration
- ✅ Minimal code footprint
- ✅ **Verified consistent results** - all versions produce identical output
