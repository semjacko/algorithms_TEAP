// uloha2-2.c -- Róbert Jačko, 24.2.2021 07:59

#include <stdio.h>
#include <stdbool.h>

unsigned long table[10][10];

// vrati pocet cislic v cisle
int getNumOfDigits(unsigned long number) {
   long int n = number, count = 0;
   while (n != 0) {
        n /= 10;
        count++;
    }

    return count;
}

// naplnenie tabulky na dynamicke programovanie
void fillTable(unsigned long number, int len) {
  long int curr = number;
  for (int i = len-1; i >= 0; i--) { 
    long int mod = 10;
    for (int j = i; j >= 0; j--) {
      table[j][i] = curr % mod;
      mod *= 10;
    }
    curr /= 10;
  }
}

bool splitByPlus(int start, int end, int numOfPlus, unsigned long sum) {
  if (sum > table[start][end]) {  // ak je cielovy sucet vacsi ako cislo ktore mame aktualne
    return false;
  }
  if (numOfPlus == 0) {
    return table[start][end] == sum;
  }
  for (int i = start; i < end; i++) {  // skusaju sa vsetky medzery medzi cislami
    if (splitByPlus(i + 1, end, numOfPlus - 1, sum - table[start][i])) {
      return true;
    }
  }
  return false;
}

int main()
{
  unsigned long bigNum, sum;
  int result;
  while (scanf("%lu %lu", &bigNum, &sum) > 0) {
    if (bigNum == 0) {
      sum == 0 ? printf("0\n") : printf("IMPOSSIBLE\n");
      continue;
    }
    int len = getNumOfDigits(bigNum);  // ziska sa pocet cislic
    result = -1;
    fillTable(bigNum, len);  // naplni sa tabulka
    for (int i = 0; i < len; i++) {  // skusi sa dosadit <0,...,len) plusok 
      if (splitByPlus(0, len - 1, i, sum)) {  // ak pre nejaky pocet plusok sedi, breakne sa
        result = i;
        break;
      }
    }
    result > -1 ? printf("%d\n", result) : printf("IMPOSSIBLE\n");
  }

  return 0;
}