#include <stdalign.h>
#include <stdint.h>

struct aligned_holder {
    alignas(16) int value;
    char flag;
};

int main(void) {
    struct aligned_holder h = {42, 'a'};
    uintptr_t addr = (uintptr_t)&h.value;
    int aligned = (addr % 16u) == 0u;
    return (aligned && h.flag == 'a' && h.value == 42) ? 0 : 1;
}
