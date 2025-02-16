enum Status { INIT = 0, RUNNING = 5, FINISHED = 10 };

int main() {
    enum Status s = RUNNING;
    // Return FINISHED - s = 10 - 5 = 5.
    return FINISHED - s - 5; // Expected: 0
}
