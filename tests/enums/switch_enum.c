// switch_enum.c
enum Operation { ADD, SUB, MUL, DIV };

int main() {
    enum Operation op = MUL;
    int result = 0;
    switch (op) {
        case ADD: result = 1; break;
        case SUB: result = 2; break;
        case MUL: result = 3; break;
        case DIV: result = 4; break;
        default: result = 0;
    }
    return result;
}
