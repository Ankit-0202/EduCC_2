struct inner {
    int x;
    int y;
};

struct outer {
    struct inner in;
    int data[4];
};

struct outer example = {
    .in = {.y = 7, .x = 3},
    .data = {[0] = 1, [2] = 5, [3] = 9}
};

int main(void) {
    int ok = 1;
    ok &= example.in.x == 3;
    ok &= example.in.y == 7;
    ok &= example.data[0] == 1;
    ok &= example.data[1] == 0;
    ok &= example.data[2] == 5;
    ok &= example.data[3] == 9;
    return ok ? 0 : 1;
}
