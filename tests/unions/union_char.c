union Test {
    float f;
    char c;
};

int main(void) {
    union Test u;
    u.f = 3.14f;
    if (u.f == 3.14f)
        return 0;
    else
        return 1;
}
