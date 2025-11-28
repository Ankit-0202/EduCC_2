#define STRINGIFY_ALL(...) #__VA_ARGS__

int main(void) {
    const char *text = STRINGIFY_ALL(alpha, beta);
    return (text[0] == 'a' && text[5] == 'b') ? 0 : 1;
}
