// uloha7-1.c -- Róbert Jačko, 30.3.2021 08:46
#pragma GCC optimize ("O3")
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 10


char table[MAX_SIZE][MAX_SIZE];


int search(int pairs[], int n_rows, int n_cols, int curr, int n) {
  int counter = 0;
 
  if (n == 0) {
    for (int i = 0; i < n_cols; i++) {
      if (pairs[i] == 0 && table[curr][i] == 'Y') {
        counter++;
      }
    }
    return counter;
  }

  for (int i = curr+1; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      if (table[curr][j] == 'Y' && pairs[j] == 0) {
        pairs[j] = 1;
        counter += search(pairs, n_rows, n_cols, i, n-1);
        pairs[j] = 0;
      }
    }
  }

  return counter;
}



int main()
{
  // sem napis svoje riesenie
  int K, N, M;

  while (scanf("%d", &K) > 0) {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
      scanf("%s", table[i]);
    }

    int counter = 0, pairs[MAX_SIZE] = {0};

    for (int i = 0; i < N; i++) {
      counter += search(pairs, N, M, i, K-1);
    }

    printf("%d\n", counter);
  } 
}