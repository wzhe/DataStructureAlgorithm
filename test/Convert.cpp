//任给10进制整数n,将其转换为r进制的表示形式
#include "../src/Stack.h"
#include <stdio.h>

void convert(Stack<char> &S, int n, int base) {
  static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  if (0 < n) {
    convert(S, n / base, base);
    S.push(digit[n % base]);
  }
}

void convert_withoutrecur(Stack<char> &S, int n, int base) {
  static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  while (0 < n) {
    int remainder = n % base;
    S.push(digit[remainder]);
    n /= base;
  }
}

int main() {
  Stack<char> result;
  int a = 100;
  int base = 17;
  while (base-- > 2) {
    convert_withoutrecur(result, a, base);
    printf(" %d convert to base %d is:\t", a, base);
    while (!result.empty()) {
      printf("%c", result.pop());
    }
    printf("\n");
  }
}
