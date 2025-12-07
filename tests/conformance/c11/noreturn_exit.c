#include <stdlib.h>

_Noreturn void finish(int code) { exit(code); }

int main(void) { finish(0); }
