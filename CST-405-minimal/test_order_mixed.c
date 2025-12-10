/* Test: Mixed Order of Operations
 * Tests: Multiple operators with different precedence levels
 * Expression: 10 + 2 * 5 - 8 / 4
 * Expected: 10 + (2 * 5) - (8 / 4) = 10 + 10 - 2 = 18
 */

int result;

# main() {
    result = 10 + 2 * 5 - 8 / 4;
    print(result);
}
