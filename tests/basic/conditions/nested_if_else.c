int main() {
    int a = 10;
    int b = 20;
    int res = 0;
    if(a < b) {
        if(b - a == 10) {
            res = 1;
        } else {
            res = 2;
        }
    } else {
        res = 3;
    }
    return res;
}
