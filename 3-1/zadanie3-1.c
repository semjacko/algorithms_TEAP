// uloha3-1.c -- Róbert Jačko, 1.3.2021 20:15

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

# define MAX_LEN 50


long int table[MAX_LEN][MAX_LEN];


void reset_table() {
  for (int i = 0; i < MAX_LEN; i++) {
    for (int j = 0; j < MAX_LEN; j++) {
      table[i][j] = 0;
    }
  }
}


void init_table(char *inp) {
  int len = strlen(inp);

  // 1 znak
  for (int i = 0; i < len; i++) {
    table[i][i] = inp[i] >= '0' && inp[i] <= '9' ? 1 : 0;
  }

  // 2 znaky
  for (int i = 0; i < len - 1; i++) {
    if (inp[i] >= '0' && inp[i] <= '9' && inp[i+1] >= '0' && inp[i+1] <= '9') {
      table[i][i+1] = 1;
    } else if (inp[i] == '-' && inp[i+1] >= '0' && inp[i+1] <= '9') {
      table[i][i+1] = 1;
    } else {
      table[i][i+1] = 0;
    }
  }

}


void fill_table(int begin, int end) {
  long int res = 0;
  for (int i = begin; i < end - 1; i++) {
    res += table[begin+1][i+1] * table[i+2][end];
  }
  table[begin][end] = res;
}


bool only_digits(char *inp, int begin, int end) {
  if (end <= begin) {
    return false;
  }

  for (int i = begin; i <= end; i++) {
    if (inp[i] < '0' || inp[i] > '9') {
      return false;
    }
  }
  return true;
}


int main() {
  char inp[MAX_LEN+1];

  while (scanf("%s", inp) > 0) {
    int len = strlen(inp);

    reset_table();
    init_table(inp);
    
    for (int i = 2; i < len; i++) {
      for (int j = 0; j < len - i; j++) {
        if (inp[j] >= '0' && inp[j] <= '9') {
          table[j][j+i] = only_digits(inp, j, j+i) ? 1 : 0;
        } else {
          fill_table(j, j+i);
          if (inp[j] == '-') {
            table[j][j+i] += only_digits(inp, j+1, j+i) ? 1 : 0;
          }
        }
      }
    }
    
    printf("%li\n", table[0][len - 1]);

  }

  return 0;
}