// Test array of string pointers
int string_length(char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

int main() {
    char *words[] = {"hello", "world", "test", "array"};

    // Check lengths
    if (string_length(words[0]) != 5) return 1;
    if (string_length(words[1]) != 5) return 2;
    if (string_length(words[2]) != 4) return 3;
    if (string_length(words[3]) != 5) return 4;

    // Check specific characters
    if (words[0][0] != 'h') return 5;
    if (words[1][4] != 'd') return 6;
    if (words[2][1] != 'e') return 7;
    if (words[3][4] != 'y') return 8;

    // Iterate through array
    int total_chars = 0;
    for (int i = 0; i < 4; i++) {
        total_chars += string_length(words[i]);
    }
    if (total_chars != 19) return 9;

    return 0;
}
