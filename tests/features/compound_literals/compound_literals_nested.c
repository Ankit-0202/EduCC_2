struct Inner {
    int a;
    char b;
};

struct Outer {
    struct Inner inner;
    int x;
    char y;
};

int get_inner_a(struct Inner inner) {
    return inner.a;
}

int get_outer_x(struct Outer outer) {
    return outer.x;
}

int main() {
    // Nested compound literal
    struct Outer outer = (struct Outer){
        .inner = (struct Inner){10, 'A'},
        .x = 20,
        .y = 'B'
    };
    
    if (outer.inner.a != 10) return 1;
    if (outer.inner.b != 'A') return 1;
    if (outer.x != 20) return 1;
    if (outer.y != 'B') return 1;
    
    // Compound literal with nested access
    int result = get_inner_a((struct Inner){5, 'C'}) + 
                 get_outer_x((struct Outer){
                     .inner = (struct Inner){15, 'D'},
                     .x = 25,
                     .y = 'E'
                 });
    
    if (result != 30) return 1;  // 5 + 25 = 30
    
    return 0;
} 