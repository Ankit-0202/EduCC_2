// Test logical operators
int main() {
    int a = 10;
    int b = 5;
    int c = 0;
    
    int and_result = (a > b) && (b > c);
    int or_result = (a < b) || (b > c);
    int not_result = !(a == b);
    
    return and_result + or_result + not_result;
}