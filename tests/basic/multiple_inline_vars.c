// Function to compute the sum of numbers from 1 to n using a while loop
int sum_while(int n) {
    int sum = 0, i = 1;
    while (i <= n) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}

// Function to compute the factorial of n using a for loop
int factorial_for(int n) {
    int result = 1;
    for (int i = 1; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
}

// Main function to test both functions
int main() {
    int n = 5;
    int sum_result = sum_while(n);
    int fact_result = factorial_for(n);

    // Check if the results are correct using if-else
    if (sum_result == 15) {
        return 0;  // Success
    } else {
        return 1;  // Failure
    }
}
