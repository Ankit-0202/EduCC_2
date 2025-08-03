/*
 * Test: Variable scope and shadowing
 * Purpose: Verify that variable scope rules work correctly including shadowing
 * and lifetime Expected Behavior: Variables should follow proper scope rules
 * with correct shadowing behavior Test Cases:
 *   - Global variables
 *   - Local variables
 *   - Variable shadowing
 *   - Block scope
 *   - Function scope
 *   - Nested scopes
 * Dependencies: Basic integer types, functions
 */

// Global variables
int global_var = 100;
int global_var2 = 200;

// Function to test scope
int test_function(int param) {
  int local_var = param * 2;
  int shadowed_var = param + 10;

  // Test local variable access
  int result = local_var + shadowed_var;

  // Test global variable access
  result += global_var;

  return result;
}

// Function to test nested scope
int test_nested_scope(int param) {
  int outer_var = param;

  {
    int inner_var = outer_var + 5;
    int shadowed_var = inner_var * 2;

    // Test inner scope variables
    int inner_result = outer_var + inner_var + shadowed_var;

    {
      int deepest_var = shadowed_var + 1;
      int deepest_result = outer_var + inner_var + shadowed_var + deepest_var;

      // Test access to all scopes
      if (deepest_result !=
          (param + (param + 5) + ((param + 5) * 2) + (((param + 5) * 2) + 1))) {
        return -1;
      }
    }

    // Test that inner variables are accessible
    if (inner_result != (param + (param + 5) + ((param + 5) * 2))) {
      return -2;
    }
  }

  // Test that outer variable is still accessible
  if (outer_var != param) {
    return -3;
  }

  return outer_var;
}

int main() {
  int result = 0;

  // Test global variable access
  int global_test = global_var + global_var2;

  // Test local variable declaration
  int local_var = 42;
  int local_var2 = 10;

  // Test variable shadowing
  int shadowed_var = 5;
  {
    int shadowed_var = 15; // Shadows outer shadowed_var
    int shadow_test = shadowed_var + local_var;

    if (shadow_test != 57)
      return 1; // 15 + 42 = 57
  }

  // Test that outer shadowed_var is still accessible
  if (shadowed_var != 5)
    return 2;

  // Test function scope
  int func_result = test_function(10);
  // Expected: (10*2) + (10+10) + 100 = 20 + 20 + 100 = 140

  // Test nested scope function
  int nested_result = test_nested_scope(5);
  // Expected: 5 (return value from test_nested_scope)

  // Test block scope
  int block_var = 100;
  {
    int block_var = 200; // Shadows outer block_var
    int block_test = block_var + 50;

    if (block_test != 250)
      return 3; // 200 + 50 = 250
  }

  // Test that outer block_var is still accessible
  if (block_var != 100)
    return 4;

  // Test multiple nested scopes
  int multi_var = 1;
  {
    int multi_var = 2;
    {
      int multi_var = 3;
      {
        int multi_var = 4;
        int multi_test = multi_var + 10;

        if (multi_test != 14)
          return 5; // 4 + 10 = 14
      }

      // Test access to outer scope
      int outer_test = multi_var + 20;
      if (outer_test != 23)
        return 6; // 3 + 20 = 23
    }

    // Test access to outer scope
    int outer_test2 = multi_var + 30;
    if (outer_test2 != 32)
      return 7; // 2 + 30 = 32
  }

  // Test that outermost multi_var is still accessible
  if (multi_var != 1)
    return 8;

  // Test variable with same name in different scopes
  int same_name = 10;
  {
    int same_name = 20;
    {
      int same_name = 30;
      int same_test = same_name + 5;

      if (same_test != 35)
        return 9; // 30 + 5 = 35
    }

    int same_test2 = same_name + 15;
    if (same_test2 != 35)
      return 10; // 20 + 15 = 35
  }

  int same_test3 = same_name + 25;
  if (same_test3 != 35)
    return 11; // 10 + 25 = 35

  // Test global variable shadowing
  int global_var = 50; // Shadows global global_var
  int global_test2 = global_var + global_var2;

  // Test that global_var2 is still accessible
  if (global_test2 != 250)
    return 12; // 50 + 200 = 250

  // Test function parameter shadowing
  int param_var = 100;
  int param_test = test_function(param_var);
  // Expected: (100*2) + (100+10) + 100 = 200 + 110 + 100 = 410

  // Test complex nested scope with arithmetic
  int complex_var = 5;
  {
    int complex_var = complex_var * 2; // Uses outer complex_var
    {
      int complex_var = complex_var + 3; // Uses middle complex_var
      int complex_test = complex_var * 2;

      if (complex_test != 26)
        return 13; // (10 + 3) * 2 = 26
    }

    int complex_test2 = complex_var + 5;
    if (complex_test2 != 15)
      return 14; // 10 + 5 = 15
  }

  // Test that outermost complex_var is unchanged
  if (complex_var != 5)
    return 15;

  // Verify all results
  if (global_test != 300)
    return 16; // 100 + 200 = 300
  if (func_result != 140)
    return 17; // (10*2) + (10+10) + 100 = 140
  if (nested_result != 5)
    return 18; // Return value from test_nested_scope
  if (param_test != 410)
    return 19; // (100*2) + (100+10) + 100 = 410

  return 0; // All tests passed
}