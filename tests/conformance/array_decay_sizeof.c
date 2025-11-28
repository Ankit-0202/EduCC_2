#include <stddef.h>

int main(void) {
    int values[4] = {1, 2, 3, 4};
    int *ptr = values;
    size_t arr_size = sizeof(values);
    size_t ptr_size = sizeof(ptr);
    return (arr_size == sizeof(int) * 4 && ptr_size == sizeof(int *)) ? 0 : 1;
}
