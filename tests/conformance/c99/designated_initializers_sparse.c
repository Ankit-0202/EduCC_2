int array_values(void) {
    int values[6] = {[0] = 1, [3] = 4, [5] = 9};
    int ok = 1;
    ok &= values[0] == 1;
    ok &= values[1] == 0;
    ok &= values[2] == 0;
    ok &= values[3] == 4;
    ok &= values[4] == 0;
    ok &= values[5] == 9;
    return ok;
}

int main(void) {
    return array_values() ? 0 : 1;
}
