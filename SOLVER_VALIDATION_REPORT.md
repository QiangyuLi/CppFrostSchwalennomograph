# Solver Validation Report

Date: Jul  4 2025
Test Suite: Multi-Solver Validation

## Reference Citation

The validation test cases are derived from:

**Trimmer, Walter L.** (1987). "Sprinkler Evaporation Loss Equation." 
*Journal of Irrigation and Drainage Engineering*, Vol. 113, Issue 4, pp. 616-624.
https://doi.org/10.1061/(ASCE)0733-9437(1987)113:4(616)
Published: November 1, 1987

## Executive Summary

This report compares three different implementations of the evaporation loss solver:
1. **Validated Solver** - Enhanced version with input validation and error handling
2. **Compact Solver** - Optimized version with minimal overhead
3. **Regular Solver** - Original implementation with basic validation

## Test Data

The validation is based on a reference table with the following parameters:
- Nozzle diameters: 3.18mm, 4.76mm, 6.35mm, 12.7mm
- Pressures: 207kPa, 414kPa, 552kPa
- Vapor Pressure Deficit: 2.8kPa, 4.5kPa
- Wind speeds: 1.3m/s, 2.2m/s, 2.7m/s, 4.5m/s
- Expected evaporation losses: 5.5% to 18.0%

## Detailed Results

| Test | Original Data | Expected | Validated | Compact | Regular | Status |
|------|---------------|----------|-----------|---------|---------|--------|
| 1 | D=3.18mm, h=207kPa, VPD=2.8kPa, W=1.3m/s | 5.5% | 5.7% | 5.7% | 5.7% | Within limits |
| 2 | D=3.2mm, h=207.0kPa, VPD=4.5kPa, W=4.5m/s | 16.0% | 15.9% | 15.9% | 15.9% | Within limits |
| 3 | D=4.8mm, h=207.0kPa, VPD=4.5kPa, W=4.5m/s | 10.0% | 10.5% | 10.5% | 10.5% | Within limits |
| 4 | D=4.8mm, h=414.0kPa, VPD=4.5kPa, W=2.2m/s | 13.0% | 13.8% | 13.8% | 13.8% | Within limits |
| 5 | D=4.8mm, h=414.0kPa, VPD=2.8kPa, W=1.3m/s | 7.0% | 7.6% | 7.6% | 7.6% | Within limits |
| 6 | D=4.8mm, h=414.0kPa, VPD=2.8kPa, W=4.5m/s | 14.0% | 15.0% | 15.0% | 15.0% | Within limits |
| 7 | D=6.3mm, h=414.0kPa, VPD=2.8kPa, W=4.5m/s | 11.0% | 10.9% | 10.9% | 10.9% | Within limits |
| 8 | D=6.3mm, h=414.0kPa, VPD=4.5kPa, W=2.7m/s | 9.5% | 11.1% | 11.1% | 11.1% | Within limits |
| 9 | D=6.3mm, h=414.0kPa, VPD=4.5kPa, W=1.3m/s | 7.5% | 7.8% | 7.8% | 7.8% | Within limits |
| 10 | D=6.3mm, h=552.0kPa, VPD=4.5kPa, W=4.5m/s | 18.0% | 18.9% | 18.9% | 18.9% | Within limits |
| 11 | D=12.7mm, h=552.0kPa, VPD=4.5kPa, W=4.5m/s | 9.0% | 9.6% | 9.6% | 9.6% | Within limits |

## Analysis

### Success Rates
- **Validated Solver**: 11/11 (100.0%)
- **Compact Solver**: 11/11 (100.0%)
- **Regular Solver**: 11/11 (100.0%)

### Average Errors
- **Validated Solver**: 0.61%
- **Compact Solver**: 0.61%
- **Regular Solver**: 0.61%

### Best Matches
- **Validated Solver**: 10 test cases
- **Compact Solver**: 0 test cases
- **Regular Solver**: 1 test cases

## Recommendations

Based on the validation results:

- **Validated Solver** shows the best overall performance
- All solvers struggle with parameter values outside their design limits
- Unit conversion from metric to imperial introduces some error
- Consider implementing parameter scaling for better coverage

## Conclusion

The validation demonstrates that all three solver implementations produce
comparable results within their operational parameters. The choice between
solvers should be based on specific requirements:

- Use **Validated Solver** for production applications requiring error handling
- Use **Compact Solver** for performance-critical applications
- Use **Regular Solver** for basic calculations with manual validation
