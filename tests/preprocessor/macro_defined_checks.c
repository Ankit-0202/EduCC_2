#define FEATURE_PRESENT 1

int main(void) {
    int value = 0;
#if defined(FEATURE_PRESENT)
    value = 5;
#else
    value = 1;
#endif
    return value == 5 ? 0 : 1;
}
