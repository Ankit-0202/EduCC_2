// union_with_enum_member.c
enum Color { RED, GREEN, BLUE };

union Mix {
    int i;
    enum Color color;
};

int main() {
    union Mix m;
    m.i = 1;
    int x = m.i; // Expected: 1
    return x;
}
