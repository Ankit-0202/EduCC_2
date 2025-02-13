// local_enum.c
int main() {
    enum Status { OFF, ON };
    enum Status s = ON;
    if (s == ON)
        return 0;
    else
        return 1;
}
