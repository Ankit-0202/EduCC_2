// tests/preprocessor/header_guard.c
#ifndef HEADER_GUARD
#define HEADER_GUARD

int foo() { return 42; }

#endif // HEADER_GUARD

int main() { return foo(); }
