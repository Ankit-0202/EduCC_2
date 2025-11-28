_Thread_local int counter = 5;

int bump(void) {
    return ++counter;
}

int main(void) {
    int first = bump();
    int second = bump();
    return (first == 6 && second == 7 && counter == 7) ? 0 : 1;
}
