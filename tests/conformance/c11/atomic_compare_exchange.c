#include <stdatomic.h>

int main(void) {
    _Atomic int value = 4;
    int expected = 4;
    int success = atomic_compare_exchange_strong(&value, &expected, 9);

    int expected_fail = 7;
    int second = atomic_compare_exchange_weak(&value, &expected_fail, 11);

    int matches = success && value == 9 && expected == 4;
    matches = matches && (!second) && expected_fail == 9;
    return matches ? 0 : 1;
}
