/******************************************************************************************
 * Test of Bitmap
 ******************************************************************************************/
#include "../src/Bitmap.h"

void Eratosthenes(const int n, char *file) {
  Bitmap B(n);
  B.set(0);
  B.set(1);
  for (int i = 2; i < n; i++) {
    if (!B.test(i)) {
      for (int j = i * i; j <= n; j += i) {
        B.set(j);
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    if (!B.test(i)) {
      printf("%2d\t", i);
    }
  }
  printf("\n");
  B.dump(file);
}

int main(int argc, char *argv[]) {
  char file[] = "./xx.txt";
  int n = 1000;
  Eratosthenes(n, file);
  Bitmap B(file, n);
  for (int i = 0; i <= n; i++) {
    if (!B.test(i)) {
      printf("%2d\t", i);
    }
  }
  printf("\n");
}
