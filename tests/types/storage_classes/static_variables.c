int get_static_counter() {
    static int counter = 0;
    counter++;
    return counter;
}

int get_static_sum() {
    static int sum = 0;
    static int count = 0;
    count++;
    sum += count;
    return sum;
}

int main() {
    if (get_static_counter() != 1) return 1;
    if (get_static_counter() != 2) return 1;
    if (get_static_counter() != 3) return 1;
    
    if (get_static_sum() != 1) return 1;  // 0 + 1
    if (get_static_sum() != 3) return 1;  // 1 + 2
    if (get_static_sum() != 6) return 1;  // 3 + 3
    
    return 0;
} 