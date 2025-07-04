#!/bin/bash

echo "🔧 Running Complete Test Suite..."
echo ""

# Test 1: Original solver
echo "📋 Test 1: Original Solver"
echo "🔧 Compiling..."
g++ -std=c++17 -o test_solver test_solver.cpp ../src/solver.cpp

if [ $? -ne 0 ]; then
    echo "❌ Original solver compilation failed."
    exit 1
fi

echo "✅ Running..."
./test_solver
ORIG_EXIT_CODE=$?

if [ $ORIG_EXIT_CODE -eq 0 ]; then
    echo "✅ Original solver test passed."
else
    echo "❌ Original solver test failed."
fi

echo ""

# Test 2: Compact solver
echo "📋 Test 2: Compact Solver"
echo "🔧 Compiling..."
g++ -std=c++17 -o test_compact_solver test_compact_solver.cpp

if [ $? -ne 0 ]; then
    echo "❌ Compact solver compilation failed."
    exit 1
fi

echo "✅ Running..."
./test_compact_solver
COMPACT_EXIT_CODE=$?

if [ $COMPACT_EXIT_CODE -eq 0 ]; then
    echo "✅ Compact solver test passed."
else
    echo "❌ Compact solver test failed."
fi

echo ""

# Test 3: Validated solver
echo "📋 Test 3: Validated Solver"
echo "🔧 Compiling..."
g++ -std=c++17 -o test_validated_solver test_validated_solver.cpp

if [ $? -ne 0 ]; then
    echo "❌ Validated solver compilation failed."
    exit 1
fi

echo "✅ Running..."
./test_validated_solver
VALIDATED_EXIT_CODE=$?

if [ $VALIDATED_EXIT_CODE -eq 0 ]; then
    echo "✅ Validated solver test passed."
else
    echo "❌ Validated solver test failed."
fi

echo ""

# Test 4: Table validation
echo "📋 Test 4: Table Validation"
echo "🔧 Compiling..."
g++ -std=c++17 -o test_table_validation test_table_validation.cpp

if [ $? -ne 0 ]; then
    echo "❌ Table validation compilation failed."
    exit 1
fi

echo "✅ Running..."
./test_table_validation
TABLE_EXIT_CODE=$?

if [ $TABLE_EXIT_CODE -eq 0 ]; then
    echo "✅ Table validation test passed."
else
    echo "❌ Table validation test failed."
fi

echo ""

# Summary
echo "📊 Test Summary:"
if [ $ORIG_EXIT_CODE -eq 0 ]; then
    echo "✅ Original solver: PASSED"
else
    echo "❌ Original solver: FAILED"
fi

if [ $COMPACT_EXIT_CODE -eq 0 ]; then
    echo "✅ Compact solver: PASSED"
else
    echo "❌ Compact solver: FAILED"
fi

if [ $VALIDATED_EXIT_CODE -eq 0 ]; then
    echo "✅ Validated solver: PASSED"
else
    echo "❌ Validated solver: FAILED"
fi

if [ $TABLE_EXIT_CODE -eq 0 ]; then
    echo "✅ Table validation: PASSED"
else
    echo "❌ Table validation: FAILED"
fi

echo ""
echo "🧹 Cleaning up..."
rm -f test_solver test_compact_solver test_validated_solver test_table_validation

# Check overall result
if [ $ORIG_EXIT_CODE -eq 0 ] && [ $COMPACT_EXIT_CODE -eq 0 ] && [ $VALIDATED_EXIT_CODE -eq 0 ] && [ $TABLE_EXIT_CODE -eq 0 ]; then
    echo "🎉 All tests passed!"
    exit 0
else
    echo "❌ Some tests failed."
    exit 1
fi
