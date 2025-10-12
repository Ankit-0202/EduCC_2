// Test matrix operations
int main() {
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int result[3][3];
    
    // Matrix transpose
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            result[i][j] = matrix[j][i];
        }
    }
    
    int sum = 0;
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 3; j = j + 1) {
            sum = sum + result[i][j];
        }
    }
    
    return sum;
}
