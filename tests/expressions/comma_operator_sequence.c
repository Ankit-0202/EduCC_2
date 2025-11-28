int main(void) {
    int x = 1;
    int y = (++x, x += 2, x * 2);
    return (x == 4 && y == 8) ? 0 : 1;
}
