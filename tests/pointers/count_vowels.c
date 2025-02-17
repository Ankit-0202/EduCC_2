int main() {
    char str[] = "hello world";
    char *ptr = str;
    int count = 0;
    int i;
    for (i = 0; *(ptr + i) != '\0'; i++) {
        char c = *(ptr + i);
        // Check for vowels (only lowercase considered)
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;  // "hello world" has 3 vowels (e, o, o)
}
