// uloha1-2.c -- Róbert Jačko, 17.2.2021 08:34

#include <stdio.h>

void vynuluj_pole(int pole[], int dlzka) {
  for (int i = 0; i < dlzka; i++) {
    pole[i] = 0;
  }
}

int kg2idx(int kg) {
  return kg - 101;  // cisla zacinaju od 101
}

int idx2kg(int idx) {
  return idx + 101;
}

int get_min_idx(int pole[], int dlzka, int start) {
  for (int i = start; i < dlzka; i++) {
    if (pole[i] > 0) {
      return i;
    }
  }
  return -1;
}

int get_max_idx(int pole[], int start) {
  for (int i = start; i >= 0; i--) {
    if (pole[i] > 0) {
      return i;
    }
  }
  return -1;
}

int main(void)
{
  int n, x[99];  // iba od 101 do 199 pretoze vsetko nad musi ist samostatne do kamiona

  while (scanf("%d", &n) > 0) {
    vynuluj_pole(x, 99);
    int kamiony = 0;
    for (int i = 0; i < n; i++) {
      int vstup;
      scanf("%d", &vstup);
      if (vstup > 199) {
        kamiony++;
      } else {
        x[kg2idx(vstup)]++;
      }
    }
      
    int min_idx = get_min_idx(x, 99, 0);
    int max_idx = get_max_idx(x, 98);
    while (max_idx >= 0 && min_idx >= 0) {
      kamiony++;
      if (idx2kg(min_idx) + idx2kg(max_idx) > 300) {
        x[max_idx]--;
      } else {
        x[min_idx]--;
        x[max_idx]--;
      }
        min_idx = get_min_idx(x, 99, min_idx);
        max_idx = get_max_idx(x, max_idx);
    }
    printf("%d\n", kamiony);
  }
  return 0;
}