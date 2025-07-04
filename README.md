# Evaporation Loss Solver (C++ Version)

This project provides a C++ implementation of the Frost & Schwalen nomograph method for estimating evaporation loss during sprinkler irrigation.

It performs the same calculation as the MATLAB version by:

* Interpolating vapor pressure deficit, nozzle diameter, pressure, and wind velocity values.
* Computing geometric pivot points based on nomograph layout.
* Intersecting these lines to determine percent evaporation loss.

---

## ✅ Features

* Pure C++ implementation
* Uses standard library only
* Interpolation logic built-in (no external dependencies)
* Simple structure for integration and testing

---

## 🔧 Build Instructions

Make sure you have a C++ compiler installed (like `g++`):

```bash
g++ -std=c++17 -o evap_solver src/main.cpp src/solver.cpp
```

Then run:

```bash
./evap_solver
```

---

## 🧪 Running Tests

To build and run the tests:

```bash
cd tests
./run_tests.sh
```

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
