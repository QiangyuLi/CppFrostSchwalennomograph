#!/bin/bash

echo "🔧 Running Full Test Suite..."
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

echo ""
echo "🧹 Cleaning up..."
rm -f test_solver

exit $TEST_EXIT_CODE
