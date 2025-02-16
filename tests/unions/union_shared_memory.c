union Data {
    int i;
    int j;
};

int main() {
    union Data d;
    d.i = 15;
    // Accessing d.j should give the same value as d.i.
    return d.j - 15; // Expected: 0
}
