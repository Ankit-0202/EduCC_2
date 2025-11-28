#include <stdio.h>

struct Node {
    int val;
    struct Node *next;
};

int main() {
    struct Node n1 = {1, NULL};
    struct Node n2 = {2, &n1};
    printf("%d -> %d\n", n2.val, n2.next->val);
    return 0;
}

