enum ShapeType { CIRCLE, SQUARE, TRIANGLE };

struct Shape {
    enum ShapeType type;
    int dimension;
};

int main() {
    struct Shape s;
    s.type = TRIANGLE;
    s.dimension = 5;
    /* If the shape is TRIANGLE, the test expects dimension * 2,
       otherwise just the dimension. For TRIANGLE: 5 * 2 = 10.
    */
    if(s.type == TRIANGLE)
        return (s.dimension * 2) - 10;
    else
        return s.dimension - 5;
}
