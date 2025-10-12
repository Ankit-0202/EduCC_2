// Test stringification
#define STRINGIFY(x) #x
#define CONCAT(a, b) a##b

int main() {
    int CONCAT(var, 1) = 10;
    int CONCAT(var, 2) = 20;
    
    return var1 + var2;
}
