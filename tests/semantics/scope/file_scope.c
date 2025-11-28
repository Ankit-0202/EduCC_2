int global_var = 42;
static int static_var = 100;

int get_global() {
    return global_var;
}

int get_static() {
    return static_var;
}

int main() {
    if (get_global() != 42) return 1;
    if (get_static() != 100) return 1;
    
    global_var = 50;
    if (global_var != 50) return 1;
    
    return 0;
} 