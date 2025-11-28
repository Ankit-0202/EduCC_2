// Test character escape sequences
int main() {
    // Newline
    char newline = '\n';
    if (newline != 10) return 1;

    // Tab
    char tab = '\t';
    if (tab != 9) return 2;

    // Carriage return
    char cr = '\r';
    if (cr != 13) return 3;

    // Backslash
    char backslash = '\\';
    if (backslash != 92) return 4;

    // Single quote
    char quote = '\'';
    if (quote != 39) return 5;

    // Double quote
    char dquote = '\"';
    if (dquote != 34) return 6;

    // Null character
    char null = '\0';
    if (null != 0) return 7;

    // Bell
    char bell = '\a';
    if (bell != 7) return 8;

    // Backspace
    char bs = '\b';
    if (bs != 8) return 9;

    return 0;
}
