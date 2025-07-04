#!/bin/bash
echo "🔧 Compiling test..."
g++ -std=c++17 -o test_solver test_solver.cpp ../src/solver.cpp

if [ $? -ne 0 ]; then
    echo "❌ Compilation failed."
    exit 1
fi

echo "✅ Running test..."
./test_solver
TEST_EXIT_CODE=$?

if [ $TEST_EXIT_CODE -eq 0 ]; then
    echo "✅ Test passed."
else
    echo "❌ Test failed with exit code $TEST_EXIT_CODE."
fi

echo "🧹 Cleaning up..."
rm -f test_solver

exit $TEST_EXIT_CODE
