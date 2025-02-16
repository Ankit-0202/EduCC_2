enum Mode { MODE_A = 1, MODE_B = 2 };

struct Data {
    int value;
};

union Container {
    struct Data d;
    enum Mode m;
};

int main() {
    union Container c;
    c.d.value = MODE_B;
    return c.m - MODE_B;
}
