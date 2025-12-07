int global_result = 0;

void set_result(int value) { global_result = value; }

void increment_result() { global_result++; }

void add_to_result(int value) { global_result += value; }

int main() {
  set_result(10);
  if (global_result != 10)
    return 1;

  increment_result();
  if (global_result != 11)
    return 1;

  add_to_result(5);
  if (global_result != 16)
    return 1;

  increment_result();
  if (global_result != 17)
    return 1;

  return 0;
}