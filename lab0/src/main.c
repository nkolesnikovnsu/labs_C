#include <stdio.h>

#include <string.h>

#include <ctype.h>


int main() {
  const char digits[] = "0123456789abcdef";
  char b1Not[128], b2Not[128];
  long long int b1, b2, lenB1Not, b1Period, b2Period, i, nPeriod = 0, frac = 0;
  long long int intPart, fracPart;
  long long int scannedCount = scanf("%lld%lld%100s", & b1, & b2, b1Not);
  if (scannedCount != 3) {
    printf("not enough input data\n");
    return 1;
  }
  lenB1Not = strlen(b1Not);
  for (i = 0; i < lenB1Not; i++) {
    if (b1Not[i] == '.')
      nPeriod++;
    else if (!strchr(digits, tolower(b1Not[i])) || strchr(digits, tolower(b1Not[i])) - digits >= b1)
      break;
    else if (b1Not[i] != '0' && nPeriod > 0)
      frac = 1;
  }
  if (nPeriod > 1 || b1Not[0] == '.' || b1Not[lenB1Not - 1] == '.' || i < lenB1Not || b1 < 2 || 16 < b1 || b2 < 2 || 16 < b2) {
    printf("bad input");
    return 0;
  }
  if (nPeriod == 0) {
    strcat(b1Not, ".0");
    lenB1Not += 2;
  }
  b1Period = strchr(b1Not, '.') - b1Not;
  intPart = 0;
  for (i = 0; i < b1Period; i++) intPart = intPart * b1 + (strchr(digits, tolower(b1Not[i])) - digits);
  fracPart = 0;
  long long int del = 1;
  for (i = b1Period + 1; i < lenB1Not; i++) {
    fracPart = fracPart * b1 + (strchr(digits, tolower(b1Not[i])) - digits);
    del = del * b1;
  }
  b2Period = 0;
  while (intPart != 0) {
    int f = intPart % b2;
    b2Not[b2Period++] = digits[f];
    intPart = (intPart - f) / b2;
  }
  if (b2Period == 0) printf("0");
  else {
    for (i = b2Period - 1; i >= 0; i--)
      printf("%c", b2Not[i]);
  }
  if (frac) {
    printf(".");
    int z = 0;
    while (fracPart > 0 && z < 12) {
      fracPart = fracPart * b2;
      int c = fracPart / del;
      fracPart = fracPart - c * del;
      printf("%c", digits[c]);
      z = z + 1;
    }
  }
  printf("\n");
  return 0;
}
