// uloha4-1.c -- Róbert Jačko, 17.3.2021 08:02

#include <stdio.h>
#define MODULER 100000007

int table[2][201] = { 0 }; // max 200 m vysoke, potrebujem 2 taketo stlpce

int countPaths(int D, int V) {
  if (V < 1 || V * 2 - 1 > D ) return 0;
  if (V == 1) return 1;

  int currHeight = 2, currWidth = 2;
  int oldCol = 0, newCol = 1;
  table[0][1] = 1;
  // ASCENDING
  while (currHeight < V) {
    for (int j = 1; j <= currHeight; j++) {
      table[newCol][j] = 0;
      if (j - 1 >= 1) {
        table[newCol][j] += table[oldCol][j - 1]; 
      }
      if (currWidth - 1 >= 1 && j <= currHeight - 1) {
        table[newCol][j] += table[oldCol][j]; 
      }
      if (j + 1 <= currHeight - 1) {
        table[newCol][j] += table[oldCol][j + 1]; 
      }
      table[newCol][j] %= MODULER;
      //printf("%d ", table[newCol][j]);
    }
    //printf("\n");
    newCol = !newCol;
    oldCol = !oldCol;
    currHeight++;
    currWidth++;
  }

  // FLAT
  while (D - currWidth > currHeight) {
    for (int j = 1; j <= currHeight; j++) {
      table[newCol][j] = 0;
      if (j - 1 >= 1) {
        table[newCol][j] += table[oldCol][j - 1]; 
      }
      table[newCol][j] += table[oldCol][j];
      if (j + 1 <= currHeight) {
        table[newCol][j] += table[oldCol][j + 1]; 
      }
      table[newCol][j] %= MODULER; 
      //printf("%d ", table[newCol][j]);
    }
    //printf("\n");
    newCol = !newCol;
    oldCol = !oldCol;
    currWidth++;
  }

  currHeight--;
  // DESCEND
  while (currHeight >= 1) {
    for (int j = 1; j <= currHeight; j++) {
      table[newCol][j] = 0;
      if (j - 1 >= 1) {
        table[newCol][j] += table[oldCol][j - 1]; 
      }
      if (currWidth - 1 >= 0) {
        table[newCol][j] += table[oldCol][j]; 
      }
      table[newCol][j] += table[oldCol][j + 1];
      table[newCol][j] %= MODULER; 
      //printf("%d ", table[newCol][j]);
    }
    //printf("\n");
    newCol = !newCol;
    oldCol = !oldCol;
    currHeight--;
    currWidth++;
  }

  return table[oldCol][1];
}

void resetTable() {
  for (int i = 0; i < 201; i++) {
    table[0][i] = 0;
    table[1][i] = 0;
  }
} 

int main()
{
  int N;
  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    int D, V;
    scanf("%d %d", &D, &V);
    int all = countPaths(D + 1, V);
    resetTable();
    int wrong = countPaths(D + 1, V - 1);
    resetTable();
    int res = all - wrong;
    res = res < 0 ? res + MODULER : res;
    printf("%d\n", res);    
  }

  return 0;
}