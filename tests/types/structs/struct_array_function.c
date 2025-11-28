struct Student {
    int id;
    char name[20];
    float grade;
};

int find_student(struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
}

float average_grade(struct Student students[], int count) {
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += students[i].grade;
    }
    return sum / count;
}

int main() {
    struct Student students[3] = {
        {1, "Alice", 85.5},
        {2, "Bob", 92.0},
        {3, "Charlie", 78.5}
    };
    
    // Test find function
    int index = find_student(students, 3, 2);
    if (index != 1) return 1;
    
    index = find_student(students, 3, 5);
    if (index != -1) return 1;
    
    // Test average function
    float avg = average_grade(students, 3);
    if (avg < 85.3 || avg > 85.4) return 1;  // (85.5+92.0+78.5)/3 = 85.33...
    
    return 0;
} 