#!/bin/bash
# Comprehensive test suite for While Loops and Order of Operations

echo "=========================================="
echo "WHILE LOOP AND ORDER OF OPERATIONS TESTS"
echo "=========================================="
echo ""

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

total_tests=0
passed_tests=0
failed_tests=0

# Function to run a test
run_test() {
    local test_name=$1
    local test_file=$2
    local expected_output=$3
    
    echo -e "${BLUE}Testing: ${test_name}${NC}"
    echo "File: ${test_file}"
    
    # Compile
    ./minicompiler ${test_file} ${test_file%.c}.s > /dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ COMPILATION FAILED${NC}"
        echo ""
        failed_tests=$((failed_tests + 1))
        total_tests=$((total_tests + 1))
        return
    fi
    
    # Run with SPIM
    actual_output=$(spim -file ${test_file%.c}.s 2>&1 | grep -v "SPIM\|Copyright\|Loaded\|All Rights\|See the file README" | grep -v "^$" | tail -n +1)
    
    echo "Expected: ${expected_output}"
    echo "Actual:   ${actual_output}"
    
    if [ "$actual_output" = "$expected_output" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        passed_tests=$((passed_tests + 1))
    else
        echo -e "${RED}✗ FAILED${NC}"
        failed_tests=$((failed_tests + 1))
    fi
    
    total_tests=$((total_tests + 1))
    echo ""
}

echo "=========================================="
echo "WHILE LOOP TESTS"
echo "=========================================="
echo ""

run_test "Basic While Loop" "test_while_basic.c" "0
1
2
3
4
5"

run_test "While Loop Accumulator (Factorial)" "test_while_accumulator.c" "120"

run_test "Nested While Loops" "test_while_nested.c" "0
0
1
2
1
0
1
2"

run_test "While Loop Complex Conditions" "test_while_condition.c" "10
9
8
7
6"

echo "=========================================="
echo "ORDER OF OPERATIONS TESTS"
echo "=========================================="
echo ""

run_test "Multiplication before Addition" "test_order_basic.c" "14"

run_test "Division before Subtraction" "test_order_division.c" "15"

run_test "Mixed Operations" "test_order_mixed.c" "18"

run_test "Left Associativity" "test_order_associativity.c" "12"

run_test "Comparison with Arithmetic" "test_order_comparison.c" "1"

echo "=========================================="
echo "COMBINED FEATURE TESTS"
echo "=========================================="
echo ""

run_test "While Loop + Order of Operations" "test_combined_while_order.c" "0
2
6
12
20"

echo "=========================================="
echo "TEST SUMMARY"
echo "=========================================="
echo "Total Tests:  ${total_tests}"
echo -e "Passed:       ${GREEN}${passed_tests}${NC}"
echo -e "Failed:       ${RED}${failed_tests}${NC}"
echo "=========================================="

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}All tests passed! ✓${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed. ✗${NC}"
    exit 1
fi
