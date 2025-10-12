// Test struct arrays
struct Point {
    int x;
    int y;
};

int main() {
    struct Point points[3];
    
    for (int i = 0; i < 3; i = i + 1) {
        points[i].x = i * 10;
        points[i].y = i * 20;
    }
    
    int sum = 0;
    for (int i = 0; i < 3; i = i + 1) {
        sum = sum + points[i].x + points[i].y;
    }
    
    return sum;
}