/*
 * Test: Invalid syntax error handling
 * Purpose: Verify that the compiler properly detects and reports syntax errors
 * Expected Behavior: Compiler should fail with appropriate error messages
 * Test Cases:
 *   - Missing semicolons
 *   - Unmatched parentheses
 *   - Invalid variable names
 *   - Malformed expressions
 *   - Incomplete statements
 * Dependencies: None (this test should fail compilation)
 */

int main() {
  // This file contains intentional syntax errors
  // The compiler should fail to compile this file

    int x = 5  // Missing semicolon
    
    int y = (3 + 4;  // Unmatched parenthesis
    
    int 123invalid = 10;  // Invalid variable name
    
    int z = 5 + ;  // Incomplete expression
    
    if (x > 3 {  // Missing closing parenthesis
    return 0;

    return 0; // Missing closing brace