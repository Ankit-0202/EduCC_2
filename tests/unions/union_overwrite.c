union Data {
    int x;
    int y;
};

int main() {
    union Data d;
    d.x = 100;
    d.y = 200; // This overwrites x.
    return d.x - 200; // Expected: 0
}
