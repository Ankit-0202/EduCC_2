int main() {
  char buffer[100];
  char user_input[50] = "Hello %s %d %x";

  // This could be a format string vulnerability
  // In a real scenario, user_input would come from user input
  sprintf(buffer, user_input, "World", 42, 0x1234);

  // Test with various format specifiers
  char test_buffer[100];
  sprintf(test_buffer, "%s %d %f %x", "Test", 123, 3.14, 0xABCD);

  // Test with potential problematic format strings
  char dangerous[50] = "%n %s %p";
  // Note: %n is dangerous as it writes to memory

  return 0;
}