// uloha2-1.c -- Róbert Jačko, 24.2.2021 07:57

#include <stdio.h>
#include <stdbool.h>
  
// tabulka medzivypoctov (dynamicke programovanie)
// na kazdom indexe je informacia, ci pri danych tahoch a pocte ceruziek je mozne vyhrat
bool table[100000];

void calcIndex(int moves[], int moves_len, int index) {
  table[index] = false;
  for (int i = 0; i < moves_len; i++) {
    if (index - moves[i] >= 0) {
      if (!table[index - moves[i]]) {
        table[index] = true;
      }
    }
  }
}

void calcWinsFirstPlayer(int moves[], int moves_len, int num) {
  table[0] = false;
  for (int i = 0; i <= num; i++) {
    calcIndex(moves, moves_len, i);
  }
}

int main()
{
 // tu si mozete nieco testovat
  int n, T[50], a, b;

  while (scanf("%d", &n) > 0) {
    for (int i = 0; i < n; i++) {
      scanf("%d", &T[i]);
    }
    scanf("%d %d", &a, &b);
    calcWinsFirstPlayer(T, n, b);
    int result = 0;
    for (int i = a; i <= b; i++) {
      if (table[i]) {
        result++;
      }
    }
    printf("%d\n", result);
  }

  

  return 0;
}