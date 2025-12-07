int global_counter = 0;

void increment_counter() {
  int temp = global_counter;
  temp = temp + 1;
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

  return 0;
}