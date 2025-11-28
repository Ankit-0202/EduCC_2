int main() {
    char str1[10] = "Hello";
    char str2[10] = "World";
    char result[20];
    
    int i = 0;
    while (str1[i] != '\0') {
        result[i] = str1[i];
        i++;
    }
    
    int j = 0;
    while (str2[j] != '\0') {
        result[i + j] = str2[j];
        j++;
    }
    result[i + j] = '\0';
    
    if (result[0] == 'H' && result[4] == 'o' && result[5] == 'W' && result[9] == 'd') {
        return 0;
    }
    return 1;
} 