#include <stdatomic.h>

int main(void) {
    _Atomic int value = 2;
    int old = atomic_fetch_add(&value, 3);
    int now = atomic_load(&value);
    return (old == 2 && now == 5) ? 0 : 1;
}
