#!/bin/bash
# Test all demo programs for the video presentation

echo "================================================"
echo "Testing Loop Demonstration Programs"
echo "================================================"
echo ""

# Demo 1: Simple counter
echo "1. Testing Simple Counter (Expected: 0, 1, 2, 3, 4)"
echo "   Compiling demo_loop_counter.c..."
./minicompiler demo_loop_counter.c demo_loop_counter.s > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "   ✓ Compilation successful"
    echo "   Running with SPIM:"
    spim -file demo_loop_counter.s 2>&1 | grep -v "SPIM Version" | grep -v "Copyright" | grep -v "All Rights" | grep -v "README" | grep -v "Loaded:" | grep -v "^$"
else
    echo "   ✗ Compilation failed"
fi
echo ""

# Demo 2: Sum calculation
echo "2. Testing Sum Calculation (Expected: 15)"
echo "   Compiling demo_loop_sum.c..."
./minicompiler demo_loop_sum.c demo_loop_sum.s > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "   ✓ Compilation successful"
    echo "   Running with SPIM:"
    spim -file demo_loop_sum.s 2>&1 | grep -v "SPIM Version" | grep -v "Copyright" | grep -v "All Rights" | grep -v "README" | grep -v "Loaded:" | grep -v "^$"
else
    echo "   ✗ Compilation failed"
fi
echo ""

# Demo 3: Nested loops
echo "3. Testing Nested Loops (Expected: 0, 1, 2, 10, 11, 12, 20, 21, 22)"
echo "   Compiling demo_loop_nested.c..."
./minicompiler demo_loop_nested.c demo_loop_nested.s > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "   ✓ Compilation successful"
    echo "   Running with SPIM:"
    spim -file demo_loop_nested.s 2>&1 | grep -v "SPIM Version" | grep -v "Copyright" | grep -v "All Rights" | grep -v "README" | grep -v "Loaded:" | grep -v "^$"
else
    echo "   ✗ Compilation failed"
fi
echo ""

# Show assembly snippet for video
echo "================================================"
echo "Sample MIPS Assembly for While Loop:"
echo "================================================"
grep -A 15 "# While loop" demo_loop_sum.s | head -16
echo ""

echo "================================================"
echo "All demos ready for video presentation!"
echo "================================================"
