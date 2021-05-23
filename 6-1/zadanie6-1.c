// uloha6-1.c -- Róbert Jačko, 30.3.2021 08:54

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printArr(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void N_K(int N, int K, int variations[], int depth) {
  if (N <= 0) {
    printArr(variations, depth);
    return;
  }
  for (int i = 0; i < K; i++) {
    variations[depth] = i + 1; 
    N_K(N - 1, K, variations, depth + 1);
  }
}

int main()
{
  int N, K, *variations;
  scanf("%d %d", &N, &K);
  variations = malloc(N * sizeof(int));
  N_K(N, K, variations, 0);

  return 0;
}