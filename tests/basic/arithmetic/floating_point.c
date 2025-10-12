// Test floating point arithmetic
int main() {
    float f1 = 3.14f;
    float f2 = 2.86f;
    float sum = f1 + f2;
    float diff = f1 - f2;
    float prod = f1 * f2;
    float quot = f1 / f2;
    
    // Convert to int for return
    return (int)(sum + diff + prod + quot);
}
