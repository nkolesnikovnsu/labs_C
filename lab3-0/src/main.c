#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

int input(int k, int * mas) {
  int i, c = 0;
  if (mas == NULL) return 0;
  for (i = 0; i < k; ++i) {
    c += (scanf("%d", & mas[i]));
  }
  if (c != k) return 0;
  return 0;
}
void sort(int l, int r, int * mas) {
  int i, j, x;
  i = l;
  j = r;
  x = mas[(i + j) / 2];
  while (i <= j) {
    while (mas[i] < x) i++;
    while (mas[j] > x) j--;
    if (i <= j) {
      if (i < j) {
        int z = mas[i];
        mas[i] = mas[j];
        mas[j] = z;
      }
      i++;
      j--;
    }
  }
  if (i < r) sort(i, r, mas);
  if (j > l) sort(l, j, mas);
}

int main() {
  int L, R;
  int i;
  int n = 0;
  if (scanf("%d", & n) != 1) return 1;
  if (n < 1) return 0;
  if (n > 2000000) return 1;
  int * mas;
  mas = (int * ) malloc(n * sizeof(int));
  input(n, mas);
  L = 0;
  R = n - 1;
  sort(L, R, mas);
  for (i = 0; i < n; ++i) {
    printf("%d ", mas[i]);

  }
  free(mas);
  return 0;
}
