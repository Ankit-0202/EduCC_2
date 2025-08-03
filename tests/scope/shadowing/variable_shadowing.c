int main() {
    int x = 10;
    {
        int x = 20;
        if (x != 20) return 1;
    }
    if (x != 10) return 1;
    
    {
        int y = 30;
        {
            int y = 40;
            if (y != 40) return 1;
        }
        if (y != 30) return 1;
    }
    
    return 0;
} 