int main() {
    int sum = 0;
    int i = 1;
    while(i <= 5) {
        int j = 1;
        while(j <= i) {
            if((i + j) % 2 == 0)
                sum = sum + i * j;
            else
                sum = sum - i * j;
            j = j + 1;
        }
        i = i + 1;
    }
    /* Calculation breakdown (using integer arithmetic):
       i = 1: j = 1 → (1+1)%2==0, sum = 1*1 = 1
       i = 2: j = 1 → (2+1)%2==1, sum = 1 - 2 = -1
              j = 2 → (2+2)%2==0, sum = -1 + 4 = 3
       i = 3: j = 1 → (3+1)%2==0, sum = 3 + 3 = 6
              j = 2 → (3+2)%2==1, sum = 6 - 6 = 0
              j = 3 → (3+3)%2==0, sum = 0 + 9 = 9
       i = 4: j = 1 → (4+1)%2==1, sum = 9 - 4 = 5
              j = 2 → (4+2)%2==0, sum = 5 + 8 = 13
              j = 3 → (4+3)%2==1, sum = 13 - 12 = 1
              j = 4 → (4+4)%2==0, sum = 1 + 16 = 17
       i = 5: j = 1 → (5+1)%2==0, sum = 17 + 5 = 22
              j = 2 → (5+2)%2==1, sum = 22 - 10 = 12
              j = 3 → (5+3)%2==0, sum = 12 + 15 = 27
              j = 4 → (5+4)%2==1, sum = 27 - 20 = 7
              j = 5 → (5+5)%2==0, sum = 7 + 25 = 32
       Expected final sum = 32.
    */
    return sum - 32;
}
