#!/bin/bash
# Compile and run with performance metrics

if [ $# -lt 2 ]; then
    echo "Usage: $0 <source.c> <output.s>"
    echo "Example: $0 test_simple.c test_simple.s"
    exit 1
fi

SOURCE=$1
OUTPUT=$2

echo "╔════════════════════════════════════════════════════════════╗"
echo "║     COMPILER WITH PERFORMANCE METRICS                      ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

# Compile
./minicompiler "$SOURCE" "$OUTPUT"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo ""
    echo "┌──────────────────────────────────────────────────────────┐"
    echo "│ EXECUTION PHASE: Running in SPIM Simulator               │"
    echo "└──────────────────────────────────────────────────────────┘"
    
    # Measure execution time
    START=$(date +%s%N)
    OUTPUT_RESULT=$(spim -file "$OUTPUT" 2>&1 | grep -v "SPIM Version" | grep -v "Copyright" | grep -v "All Rights" | grep -v "README" | grep -v "Loaded:" | grep -v "^$")
    END=$(date +%s%N)
    
    # Calculate execution time in milliseconds
    EXEC_TIME=$(echo "scale=3; ($END - $START) / 1000000" | bc)
    
    echo ""
    echo "Program Output:"
    echo "───────────────────────────────────────────────────────────"
    echo "$OUTPUT_RESULT"
    echo "───────────────────────────────────────────────────────────"
    echo ""
    echo "╔════════════════════════════════════════════════════════════╗"
    echo "║ EXECUTION METRICS                                          ║"
    echo "╠════════════════════════════════════════════════════════════╣"
    printf "║ Execution Time: %10.3f ms                           ║\n" "$EXEC_TIME"
    echo "╚════════════════════════════════════════════════════════════╝"
else
    echo "✗ Compilation failed"
    exit 1
fi
