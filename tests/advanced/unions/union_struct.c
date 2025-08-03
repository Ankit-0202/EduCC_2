struct Point {
    int x;
    int y;
};

struct Circle {
    struct Point center;
    int radius;
};

struct Rectangle {
    struct Point top_left;
    struct Point bottom_right;
};

union Shape {
    struct Circle circle;
    struct Rectangle rectangle;
};

int main() {
    union Shape shape;
    
    // Use as circle
    shape.circle.center.x = 10;
    shape.circle.center.y = 20;
    shape.circle.radius = 5;
    
    if (shape.circle.center.x != 10) return 1;
    if (shape.circle.center.y != 20) return 1;
    if (shape.circle.radius != 5) return 1;
    
    // Use as rectangle
    shape.rectangle.top_left.x = 0;
    shape.rectangle.top_left.y = 0;
    shape.rectangle.bottom_right.x = 10;
    shape.rectangle.bottom_right.y = 10;
    
    if (shape.rectangle.top_left.x != 0) return 1;
    if (shape.rectangle.top_left.y != 0) return 1;
    if (shape.rectangle.bottom_right.x != 10) return 1;
    if (shape.rectangle.bottom_right.y != 10) return 1;
    
    return 0;
} 