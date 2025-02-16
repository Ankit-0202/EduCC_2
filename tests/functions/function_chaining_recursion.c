int f1(int n);
int f2(int n);
int f3(int n);

int f1(int n) {
    if(n <= 0) return 0;
    return n + f2(n - 1);
}

int f2(int n) {
    if(n <= 0) return 0;
    return n + f3(n - 1);
}

int f3(int n) {
    if(n <= 0) return 0;
    return n + f1(n - 1);
}

int main() {
    /* For n = 3:
       f1(3) = 3 + f2(2)
       f2(2) = 2 + f3(1)
       f3(1) = 1 + f1(0) = 1
       So, f1(3) = 3 + (2 + 1) = 6.
    */
    return f1(3) - 6;
}
