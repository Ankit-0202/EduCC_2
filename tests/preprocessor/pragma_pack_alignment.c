#include <stddef.h>

_Pragma("pack(push, 1)")
struct packed_value {
    char c;
    int x;
};
_Pragma("pack(pop)")

int main(void) {
    return sizeof(struct packed_value) == 5 ? 0 : 1;
}
