union Number {
    int i;
    float f;
};

int main() {
    union Number num;
    num.i = 1065353216; // Bit pattern for float 1.0 on many systems (IEEE 754)
    // Convert the float value to int by multiplying by 10 and truncating.
    // Expected: 1.0 * 10 = 10.
    int result = (int)(num.f * 10);
    return result - 10; // Expected: 0
}
