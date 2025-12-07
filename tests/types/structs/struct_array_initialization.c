struct Student {
  int id;
  char name[20];
  float grade;
};

int main() {
  struct Student students[3] = {
      {1, "Alice", 85.5}, {2, "Bob", 92.0}, {3, "Charlie", 78.5}};

  if (students[0].id != 1)
    return 1;
  if (students[0].name[0] != 'A')
    return 1;
  if (students[0].grade < 85.4 || students[0].grade > 85.6)
    return 1;

  if (students[1].id != 2)
    return 1;
  if (students[1].name[0] != 'B')
    return 1;
  if (students[1].grade < 91.9 || students[1].grade > 92.1)
    return 1;

  if (students[2].id != 3)
    return 1;
  if (students[2].name[0] != 'C')
    return 1;
  if (students[2].grade < 78.4 || students[2].grade > 78.6)
    return 1;

  return 0;
}