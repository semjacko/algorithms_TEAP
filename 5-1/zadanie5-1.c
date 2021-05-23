// uloha5-1.c -- Róbert Jačko, 17.3.2021 08:02

#include <stdio.h>
#include <limits.h>

int main()
{

  int n, k, arr[50];

  while (scanf("%d %d", &n, &k) > 0) {

    int min = INT_MAX, max = INT_MIN, idx_stop = -1;
    
    // nacita sa cele vstupne pole a zisti sa maximalna a minimalna hodnota
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
      if (arr[i] < min) {
        min = arr[i];
      }
      if (arr[i] > max) {
        max = arr[i];
      }
      // ak uz je splnena podmienka na rozdiel max a min tak sa ulozi index
      // pri ktorom sa podmienka splnila
      if (max - min >= k && idx_stop == -1) {
        idx_stop = i;
      }
    }

    // ak nebola splnena podmienka na rozdiel max a min tak sa vypise dlzka
    // pola a pokracuje sa na dalsi input
    if (idx_stop == -1) {
      printf("%d\n", n);
      continue;
    }

    int len = idx_stop + 1; // dlzka pola kedy je uz splnena podmienka

    // test na skakanie idexov po 2
    min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < len; i += 2) {
      if (arr[i] < min) {
        min = arr[i];
      }
      if (arr[i] > max) {
        max = arr[i];
      }
    }

    int result = len / 2 + len % 2;

    // ak sa skakanim po 2 nesplni podmienka musi sa
    // niekde skocit o 1 cim sa aj predlzi cesta
    if (!(max - min >= k)) {
      result++;
    }

    printf("%d", result);
  }

  return 0;
}