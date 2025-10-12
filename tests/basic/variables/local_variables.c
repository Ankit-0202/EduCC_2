// Test local variable declarations and scope
int main() {
    int a = 10;
    int b = 20;
    int c = a + b;
    
    {
        int a = 5;  // Shadowing
        c = c + a;
    }
    
    return c;
}