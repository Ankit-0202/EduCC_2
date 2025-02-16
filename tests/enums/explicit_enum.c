enum Status { FAIL = 0, PASS = 1, UNKNOWN = 2 };

int main() {
    enum Status s = PASS;
    return s; // Expected: 1
}
