// A simple C program to test the compiler

// Recursive function to calculate factorial
int factorial(int n) {
  if (n <= 1) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

// A helper function to add two integers
int add(int a, int b) { return a + b; }

// The main function
int main() {
  int num = 5;
  int fact = factorial(num); // Calculate factorial of num
  int sum = add(num, fact);  // Add num and its factorial

  // Use an if-else statement to decide the return value
  if (sum > 100) {
    return sum; // Return sum if greater than 100
  } else {
    return 0; // Otherwise, return 0
  }
}
