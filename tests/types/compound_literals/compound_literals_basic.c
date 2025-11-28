struct Point {
    int x;
    int y;
};

int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int get_point_x(struct Point p) {
    return p.x;
}

int main() {
    // Compound literal for array
    int sum = sum_array((int[]){1, 2, 3, 4, 5}, 5);
    if (sum != 15) return 1;
    
    // Compound literal for struct
    int x = get_point_x((struct Point){10, 20});
    if (x != 10) return 1;
    
    // Compound literal for nested struct
    struct Point p = (struct Point){30, 40};
    if (p.x != 30) return 1;
    if (p.y != 40) return 1;
    
    // Compound literal in expression
    int result = sum_array((int[]){5, 10, 15}, 3) + 
                 get_point_x((struct Point){100, 200});
    if (result != 130) return 1;  // (5+10+15) + 100 = 130
    
    return 0;
} 