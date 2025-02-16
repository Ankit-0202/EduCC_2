int main() {
    int x = 100;
    {
        int x = 50;
        {
            int x = 25;
            x = x + 5; // Inner x becomes 30.
        }
        // x here is still 50.
    }
    return x; // Expected: 100
}
