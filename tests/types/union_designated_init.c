union number {
    int i;
    float f;
};

int main(void) {
    union number n = {.f = 1.5f};
    return (n.f > 1.4f && n.f < 1.6f) ? 0 : 1;
}
