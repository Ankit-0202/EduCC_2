/*
 * Test: Basic function features
 * Purpose: Verify that function declaration, definition, calls and return
 * values work correctly Expected Behavior: Functions execute properly with
 * correct parameter passing and return values Test Cases:
 *   - Function declarations and definitions
 *   - Function calls with different parameter types
 *   - Return values of different types
 *   - Multiple parameters
 *   - Function prototypes
 * Dependencies: Basic integer and floating point types
 */

// Function prototypes
int add(int a, int b);
float multiply(float a, float b);
int factorial(int n);
void no_return_function(int x);
int function_with_local_vars(int x);

// Function definitions
int add(int a, int b) { return a + b; }

float multiply(float a, float b) { return a * b; }

int factorial(int n) {
  if (n <= 1) {
    return 1;
  }
  return n * factorial(n - 1);
}

void no_return_function(int x) {
  // This function doesn't return anything
  // It's used to test void functions
}

int function_with_local_vars(int x) {
  int local_var = x * 2;
  int another_local = local_var + 10;
  return another_local;
}

int main() {
  int result = 0;

  // Test basic function calls
  int sum1 = add(5, 3);
  int sum2 = add(10, 20);
  int sum3 = add(-5, 8);

  // Test floating point functions
  float product1 = multiply(2.5f, 3.0f);
  float product2 = multiply(0.5f, 4.0f);
  float product3 = multiply(-2.0f, 3.0f);

  // Test recursive function
  int fact1 = factorial(5);
  int fact2 = factorial(0);
  int fact3 = factorial(1);

  // Test function with local variables
  int local_result1 = function_with_local_vars(5);
  int local_result2 = function_with_local_vars(10);

  // Test void function (should not cause errors)
  no_return_function(42);

  // Test function calls in expressions
  int complex_expr = add(add(1, 2), add(3, 4));
  float float_expr = multiply(multiply(2.0f, 3.0f), 4.0f);

  // Test function calls with variables
  int a = 15;
  int b = 25;
  int var_sum = add(a, b);

  float f1 = 3.14f;
  float f2 = 2.0f;
  float var_product = multiply(f1, f2);

  // Verify results
  if (sum1 != 8)
    return 1;
  if (sum2 != 30)
    return 2;
  if (sum3 != 3)
    return 3;

  if (product1 < 7.4f || product1 > 7.6f)
    return 4;
  if (product2 < 1.9f || product2 > 2.1f)
    return 5;
  if (product3 < -6.1f || product3 > -5.9f)
    return 6;

  if (fact1 != 120)
    return 7; // 5! = 120
  if (fact2 != 1)
    return 8; // 0! = 1
  if (fact3 != 1)
    return 9; // 1! = 1

  if (local_result1 != 20)
    return 10; // (5*2) + 10 = 20
  if (local_result2 != 30)
    return 11; // (10*2) + 10 = 30

  if (complex_expr != 10)
    return 12; // (1+2) + (3+4) = 10
  if (float_expr < 23.9f || float_expr > 24.1f)
    return 13; // (2*3) * 4 = 24

  if (var_sum != 40)
    return 14; // 15 + 25 = 40
  if (var_product < 6.27f || var_product > 6.29f)
    return 15; // 3.14 * 2.0 = 6.28

  // Test function calls with constants
  int const_sum = add(100, 200);
  float const_product = multiply(10.0f, 5.0f);

  if (const_sum != 300)
    return 16;
  if (const_product < 49.9f || const_product > 50.1f)
    return 17;

  return 0; // All tests passed
}