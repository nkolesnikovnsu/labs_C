#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

void swap(int * a,int * b)
{
  int c = *a;
  *a=*b;
  *b=c;
} 
void shiftDown(int * mas, int begin, int end) {
  int left = 2 * begin + 1;
  int right = left + 1;
  int maximum = left;
  while (maximum < end) {
    if (right < end) {
      if (mas[left] < mas[right]) {
        maximum = right;
      }
    }
    if (mas[begin] < mas[maximum]) {
      swap(&mas[begin],&mas[maximum]);
    } else {
      break;
    }
    begin = maximum;
    left = 2 * begin + 1;
    right = left + 1;
    maximum = left;
  }
}
void input(int k, int * mas) {
  int i, c = 0;
  if (mas == NULL) return;
  for (i = 0; i < k; ++i) {
    c += (scanf("%d", & mas[i]));
  }
}
void heapSort(int * mas, int masSize) {
  int i;
  int len = masSize;
  for (i = len / 2 - 1; i >= 0; i--) {
    shiftDown(mas, i, len);
  }
  for (i = len - 1; i > 0; i--) {
    swap(&mas[i],&mas[0]);
    shiftDown(mas, 0, i);
  }
}
int main() {
  int i;
  int n = 0;
  if (scanf("%d", & n) != 1) return 0;
  if (n < 1) return 0;
  if (n > 2000000) return 0;
  int * mas;
  mas = (int * ) malloc(n * sizeof(int));
  input(n, mas);
  heapSort(mas, n);
  for (i = 0; i < n; ++i) {
    printf("%d ", mas[i]);

  }
  free(mas);
  return 0;
}
