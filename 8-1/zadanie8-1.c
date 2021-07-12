// uloha8-1.c -- Róbert Jačko, 7.4.2021 08:33
// zdroj algoritmu Ford-Fulkerson: https://www.programiz.com/dsa/ford-fulkerson-algorithm

#pragma GCC optimize ("O1")
#include <stdio.h>

#define A 0
#define B 1
#define C 2
#define MAX_NODES 202
#define O 1000000000

int n;
int matrix[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) {
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = C;
  return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < n; u++) {
    color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < n; v++) {
      if (color[v] == A && matrix[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == C;
}

// Applying fordfulkerson algorithm
int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      flow[i][j] = 0;
    }
  }

  // Updating the residual values of edges
  while (bfs(source, sink)) {
    int increment = O;
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      increment = min(increment, matrix[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    // Adding the path flows
    max_flow += increment;
  }
  return max_flow;
}


void reset_matrix(int size) {
  for (int i = 0; i <= size; i++) {
    for (int j = 0; j <= size; j++) {
      matrix[i][j] = 0;
    }
  }
}


int main()
{
  // sem napis svoje riesenie
  int N, M;

  while (scanf("%d %d", &N, &M) > 0) {
    reset_matrix(M+1+N+1);
    int sum_friends = 0, capacity = 0, max = 0;
    for (int i = 1; i <= N; i++) {
      scanf("%d", &matrix[0][i]);
      sum_friends += matrix[0][i];
      if (max < matrix[0][i]) {
        max = matrix[0][i];
      }
    }
    for (int i = 1; i < N+1; i++) {
      for (int j = N+1; j < N+1+M; j++) {
        matrix[i][j] = 1;
      }
    }
    for (int i = N+1; i < N+1+M; i++) {
      scanf("%d", &matrix[i][N+1+M]);
      capacity += matrix[i][N+1+M];
    }

    int max_flow = 0;
    n = N+1+M+1;
    
    if (capacity - sum_friends >= 0 && max <= M) {
      int s = 0, t = M+N+1;
      max_flow = fordFulkerson(s, t);
    }
  
    printf("%d\n", max_flow == sum_friends);
  }

  return 0;
}