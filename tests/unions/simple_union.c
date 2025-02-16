union Number {
    int i;
    int j;
};

int main() {
    union Number num;
    num.i = 20;
    return num.j - 20; // Expected: 0 (members share the same memory)
}
