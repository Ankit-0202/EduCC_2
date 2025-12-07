int main() {
  auto int x = 15;
  auto char c = 'D';
  auto float f = 4.2;

  if (x != 15)
    return 1;
  if (c != 'D')
    return 1;
  if (f < 4.1 || f > 4.3)
    return 1;

  {
    auto int y = 25;
    if (y != 25)
      return 1;
  }

  auto int sum = 0;
  for (auto int i = 1; i <= 5; i++) {
    sum += i;
  }

  if (sum != 15)
    return 1; // 1+2+3+4+5 = 15

  return 0;
}