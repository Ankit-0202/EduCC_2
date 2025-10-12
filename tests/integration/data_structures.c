// Test data structures
struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node node1, node2, node3;
    
    node1.data = 10;
    node1.next = &node2;
    node2.data = 20;
    node2.next = &node3;
    node3.data = 30;
    node3.next = 0;
    
    int sum = 0;
    struct Node* current = &node1;
    while (current != 0) {
        sum = sum + current->data;
        current = current->next;
    }
    
    return sum;
}
