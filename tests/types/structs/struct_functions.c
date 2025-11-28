struct Point {
    int x;
    int y;
};

struct Point create_point(int x, int y) {
    struct Point p = {x, y};
    return p;
}

struct Point add_points(struct Point p1, struct Point p2) {
    struct Point result = {p1.x + p2.x, p1.y + p2.y};
    return result;
}

void modify_point(struct Point *p, int x, int y) {
    p->x = x;
    p->y = y;
}

int point_distance(struct Point p1, struct Point p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return dx * dx + dy * dy;  // Square of distance
}

int main() {
    struct Point p1 = create_point(10, 20);
    if (p1.x != 10) return 1;
    if (p1.y != 20) return 1;
    
    struct Point p2 = create_point(5, 15);
    if (p2.x != 5) return 1;
    if (p2.y != 15) return 1;
    
    struct Point sum = add_points(p1, p2);
    if (sum.x != 15) return 1;  // 10 + 5
    if (sum.y != 35) return 1;  // 20 + 15
    
    modify_point(&p1, 30, 40);
    if (p1.x != 30) return 1;
    if (p1.y != 40) return 1;
    
    int distance = point_distance(p1, p2);
    if (distance != 650) return 1;  // (30-5)² + (40-15)² = 25² + 25² = 625 + 25 = 650
    
    return 0;
} 