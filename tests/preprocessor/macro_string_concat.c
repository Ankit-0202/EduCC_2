#define FIRST "hello"
#define SECOND "world"

static const char *joined = FIRST " " SECOND;

int main(void) { return (joined[5] == ' ' && joined[6] == 'w') ? 0 : 1; }
