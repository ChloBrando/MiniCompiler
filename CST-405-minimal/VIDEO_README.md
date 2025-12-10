# Video Presentation Materials: Loop Implementation

## Overview
This directory contains all materials needed for the 5-minute video presentation on loop implementation in the C-minus compiler.

## Files Included

### Documentation
1. **LOOP_IMPLEMENTATION.md** - Comprehensive technical documentation covering:
   - Language syntax
   - All 5 implementation phases (lexical, syntax, AST, semantic, codegen)
   - Control flow diagrams
   - Complete working examples
   - Testing and verification

2. **VIDEO_PRESENTATION_SCRIPT.md** - Complete 5-minute presentation script with:
   - Timed sections (30s, 60s, 90s segments)
   - What to say at each point
   - What to show on screen
   - Screen recording tips
   - Backup commands

### Demo Programs
3. **demo_loop_counter.c** - Simple counter (0 to 4)
   - Best for showing basic loop structure
   - Output: 0, 1, 2, 3, 4

4. **demo_loop_sum.c** - Sum calculation (1+2+3+4+5)
   - Shows accumulation pattern
   - Output: 15

5. **demo_loop_nested.c** - Nested loops
   - Demonstrates unique label generation
   - Output: 0, 1, 2, 10, 11, 12, 20, 21, 22

### Testing
6. **test_all_demos.sh** - Automated test script
   - Compiles all demo programs
   - Runs them with SPIM
   - Shows sample assembly code
   - Verifies everything works before recording

## Video Recording Workflow

### 1. Preparation (Before Recording)
```bash
cd CST-405-minimal

# Test all demos work
./test_all_demos.sh

# Verify output is correct
# Clean up terminal
clear
```

### 2. Recording Setup
- **Screen Resolution:** 1920x1080 or 1280x720
- **Font Size:** Terminal at least 16pt
- **Recording Software:** OBS Studio, Zoom, or QuickTime
- **Duration Target:** 4:30-5:00 (allows editing buffer)

### 3. Recording Structure

**Segment 1 (0:00-0:30): Introduction**
- Show title slide
- Introduce topic
- Show simple example code

**Segment 2 (0:30-1:00): Scanner & Parser**
- Split screen: scanner.l and parser.y
- Highlight key code sections
- Explain token and grammar

**Segment 3 (1:00-2:00): AST & Semantic**
- Show AST structure definition
- Display visual AST diagram
- Show semantic validation code

**Segment 4 (2:00-3:30): Code Generation**
- Show control flow diagram
- Walk through code generation function
- Display generated MIPS assembly
- Point out key instructions

**Segment 5 (3:30-4:30): Live Demo**
- Terminal: compile demo_loop_sum.c
- Show compilation phases
- Run with SPIM
- Show output: 15
- Display execution trace

**Segment 6 (4:30-5:00): Advanced & Conclusion**
- Show nested loop code
- Display unique labels
- Summary slide
- Thank you

### 4. Quick Demo Commands

During recording, use these exact commands:

```bash
# Simple counter demo
./minicompiler demo_loop_counter.c demo_loop_counter.s
spim -file demo_loop_counter.s

# Sum demo (main feature)
./minicompiler demo_loop_sum.c demo_loop_sum.s
spim -file demo_loop_sum.s

# Show assembly
cat demo_loop_sum.s | grep -A 15 "# While loop"

# Nested loop demo
./minicompiler demo_loop_nested.c demo_loop_nested.s
spim -file demo_loop_nested.s
```

## Key Points to Cover

### Must Include (Required)
✓ Loop syntax: `while (condition) statement`  
✓ All 5 compiler phases shown  
✓ AST structure with condition and body  
✓ MIPS assembly with labels and jumps  
✓ Working demo with correct output  

### Nice to Have (Time Permitting)
- Execution trace showing iterations
- Comparison of different loop types
- Nested loop example
- Performance metrics

## Expected Outputs

### Demo 1: Counter
```
0
1
2
3
4
```

### Demo 2: Sum (Featured in video)
```
15
```
Calculation: 1+2+3+4+5 = 15

### Demo 3: Nested Loops
```
0
1
2
10
11
12
20
21
22
```
Pattern: i*10 + j for i,j in 0..2

## Visual Elements to Prepare

1. **Title Slide:**
   - "Loop Implementation in C-Minus Compiler"
   - Your name
   - CST-405 Compiler Construction

2. **Diagrams:**
   - AST tree structure
   - Control flow diagram (while loop execution)
   - Label generation illustration

3. **Code Highlights:**
   - Scanner: `"while" { return WHILE; }`
   - Parser: while_stmt grammar rule
   - AST: whileLoop struct
   - Codegen: Label generation and assembly

## Troubleshooting

### If Compilation Fails
```bash
# Rebuild compiler
make clean && make

# Verify it works
./minicompiler demo_loop_counter.c demo_loop_counter.s
```

### If SPIM Doesn't Show Output
- Check that main_code calls _user_main
- Verify assembly file has proper labels
- Try running: `spim -file output.s < /dev/null`

### If Demo Output is Wrong
- Check source code logic
- Verify variables are initialized
- Look at TAC for optimization issues

## Post-Recording

### Editing Checklist
- [ ] Trim to exactly 5:00 (±5 seconds okay)
- [ ] Add title screen (first 3 seconds)
- [ ] Add closing slide (last 3 seconds)
- [ ] Check audio levels (clear and consistent)
- [ ] Verify all code is readable
- [ ] Add captions if required

### Export Settings
- Format: MP4 (H.264)
- Resolution: 1920x1080 or 1280x720
- Frame Rate: 30 fps
- Bitrate: 5-10 Mbps

## Submission

Include with video:
1. The video file (MP4)
2. This LOOP_IMPLEMENTATION.md document
3. Source code files (demo_*.c)

---

## Quick Reference Card (Print This!)

**Time Markers:**
- 0:00 - Intro
- 0:30 - Scanner/Parser
- 1:00 - AST/Semantic
- 2:00 - Code Generation
- 3:30 - Live Demo
- 4:30 - Conclusion

**Key Phrases:**
- "Coordinated work across all phases"
- "AST node with condition and body"
- "Unique labels for each loop"
- "Proper control flow with jumps and branches"

**Commands:**
```
./minicompiler demo_loop_sum.c demo_loop_sum.s
spim -file demo_loop_sum.s
```

**Expected Output:** 15

---

*Good luck with your presentation!*  
*All materials tested and working as of December 7, 2025*
