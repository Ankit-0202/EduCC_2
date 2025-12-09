int global_counter = 0;

void increment_counter() {
  int temp = global_counter;
  temp = temp + 1;
  global_counter = temp;
}

void decrement_counter() {
  int temp = global_counter;
  temp = temp - 1;
  global_counter = temp;
}

int main() {
  // Simulate potential race condition
  // In a multi-threaded environment, this could be problematic

  // Multiple increments
  increment_counter();
  increment_counter();
  increment_counter();

  if (global_counter != 3)
    return 1;

  // Multiple decrements
  decrement_counter();
  decrement_counter();

  if (global_counter != 1)
    return 1;

  // Test with more complex operations
  for (int i = 0; i < 10; i++) {
    increment_counter();
  }

  if (global_counter != 11)
    return 1;

  for (int i = 0; i < 5; i++) {
    decrement_counter();
  }

  if (global_counter != 6)
    return 1;

  return 0;
}