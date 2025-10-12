// Test global variable declarations and initialization
int global_int = 42;
float global_float = 3.14f;
double global_double = 2.71828;
char global_char = 'A';
int global_uninitialized;

int main() {
    return global_int + (int)global_float + (int)global_double + global_char + global_uninitialized;
}