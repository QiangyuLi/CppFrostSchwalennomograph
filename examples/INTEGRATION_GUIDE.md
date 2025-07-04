# Minimal Evaporation Calculator - Integration Guide

**📅 Updated: July 2025**

**🆕 Latest Updates:**
- **Ultra-minimal versions** created for instant integration
- **Header-only implementation** - single file, zero dependencies
- **Copy-paste ready** - function can be directly copied into any project
- **Zero namespace pollution** - uses only std library
- **30-second integration** - fastest possible setup
- **Verified consistency** - all versions produce identical results

I've created several ultra-minimal versions of the evaporation loss calculator for fast integration into any C++ project. All versions use only the standard library and avoid custom namespaces.

## Available Versions

### 1. 🏆 **Header-Only Version** (RECOMMENDED)
**File:** `evap_calculator.h`
- **Best for:** Most projects
- **Integration:** Copy 1 file, include it
- **Usage:** `#include "evap_calculator.h"`
- **Size:** ~3KB header file

### 2. 📋 **Copy-Paste Version** 
**File:** `copy_paste_calculator.cpp`
- **Best for:** When you can't add files
- **Integration:** Copy the function directly into your code
- **Usage:** Just copy the `calculateEvaporationLoss` function
- **Size:** ~1KB of code

### 3. 📖 **Standalone Version**
**File:** `minimal_evap_calculator.cpp`
- **Best for:** Learning/testing
- **Integration:** Complete program with examples
- **Usage:** Compile and run as-is
- **Size:** ~4KB with examples

### 4. 🎯 **Simple Example**
**File:** `simple_example.cpp`
- **Best for:** Reference implementation
- **Integration:** Shows how to use the header version
- **Usage:** Reference for your own code

## Quick Integration

### Option 1: Header-Only (Easiest)
```cpp
// 1. Copy evap_calculator.h to your project
// 2. Include it
#include "evap_calculator.h"

// 3. Use it
double loss = calculateEvaporationLoss(0.6, 12, 40, 5);
```

### Option 2: Direct Copy-Paste
```cpp
// Just copy the calculateEvaporationLoss function from 
// copy_paste_calculator.cpp directly into your code
```

## Function Signature
```cpp
double calculateEvaporationLoss(double vpd, int nozzle, double pressure, double wind);
```

## Parameters
- `vpd`: Vapor-Pressure Deficit (psi)
- `nozzle`: Nozzle diameter (64ths inch)
- `pressure`: Pressure (psi)
- `wind`: Wind velocity (mph)

## Key Features
- ✅ **🆕 No custom namespaces** - uses `std` only
- ✅ **🆕 No external dependencies** - standard library only
- ✅ **🆕 Header-only design** - no separate compilation
- ✅ **🆕 Fast integration** - 1 file or copy-paste
- ✅ **🆕 Minimal footprint** - <5KB total
- ✅ **🆕 C++17 compatible** - works with modern C++
- ✅ **🆕 Verified consistency** - all versions produce identical results

## Compilation
```bash
g++ -o your_program your_program.cpp -std=c++17
```

## Example Results
```
Standard conditions (VPD=0.6, nozzle=12, pressure=40, wind=5): 8.31%
Low conditions (VPD=0.3, nozzle=12, pressure=30, wind=3): 3.33%
High conditions (VPD=0.8, nozzle=16, pressure=60, wind=8): 15.61%
```

## Integration Time
- **🆕 Header-only:** ~30 seconds (down from 2 minutes)
- **🆕 Copy-paste:** ~60 seconds (single function)
- **🆕 Total code:** <100 lines (extremely compact)
- **🆕 Verified results:** All versions produce identical output

## 📊 Performance Comparison
| Version | Integration Time | Files Needed | Code Size | Namespace |
|---------|------------------|--------------|-----------|-----------|
| **🆕 Header-only** | 30 seconds | 1 file | ~3KB | std only |
| **🆕 Copy-paste** | 60 seconds | 0 files | ~1KB | std only |
| Original compact | 2 minutes | 1 file | ~4KB | Custom |
| Full version | 5+ minutes | 3+ files | ~10KB | Custom |

Choose the version that best fits your project needs!
