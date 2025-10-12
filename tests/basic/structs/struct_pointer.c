// Test struct with pointer
struct Node {
    int value;
    struct Node* next;
};

int main() {
    struct Node node1;
    struct Node node2;
    
    node1.value = 10;
    node1.next = &node2;
    node2.value = 20;
    node2.next = 0;  // NULL
    
    return node1.value + node1.next->value;
}
