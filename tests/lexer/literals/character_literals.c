// Test character literals
int main() {
    // Basic ASCII characters
    char a = 'A';
    if (a != 65) return 1;

    char z = 'Z';
    if (z != 90) return 2;

    char zero = '0';
    if (zero != 48) return 3;

    char nine = '9';
    if (nine != 57) return 4;

    // Lowercase
    char lower_a = 'a';
    if (lower_a != 97) return 5;

    // Space
    char space = ' ';
    if (space != 32) return 6;

    // Special characters
    char plus = '+';
    if (plus != 43) return 7;

    char star = '*';
    if (star != 42) return 8;

    return 0;
}
