// uloha5-2.c -- Róbert Jačko, 17.3.2021 08:02

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 49


int table[MAX_SIZE][MAX_SIZE];


void reset_table() {

  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; j++) {
      table[i][j] = 0;
    }
  }

}


// inicializacia dvojic
void init_table(char *inp, int len) {

  // zaciatok a koniec
  table[0][1] = inp[1] == '<';
  table[len-2][len-1] = inp[len-2] == '>';

  // stred
  for (int i = 1; i < len - 2; i++) {
    table[i][i+1] = inp[i] == '>' || inp[i+1] == '<';
  }

}


int is_possible(char *inp, int begin, int end, int len) {

  // ak zaciatok a koniec mozu navzajom zmiznut (ale nie je to uplny zaciatok a uplny koniec pola)
  // a zaroven aj stred medzi nimi moze zmiznut
  if (((inp[begin] == '>' && begin != 0) || (inp[end] == '<' && end != len - 1)) && (table[begin+1][end-1] == 1)) {
    return 1;
  }

  // test ci nemozu zmiznut ostatne kombinacie
  for (int i = begin + 1; i < end - 1; i+=2) {
    if (table[begin][i] == 1 && table[i+1][end]) {
      return 1;
    }
  }

  return 0;
}


void fill_table(char *inp, int len) {
  for (int i = 3; i < len - 1; i+=2) {
    for (int j = 0; j < len - i; j++) {
      table[j][i + j] = is_possible(inp, j, i+j, len);
    }
  }
}


int main() {
  
  char inp[MAX_SIZE + 1];
  char out[MAX_SIZE + 1];

  // init output
  for (int i = 1; i < MAX_SIZE; i += 2) {
    out[i] = '.';
  }

  while (scanf("%s", inp) > 0) {

    reset_table();
    int len = strlen(inp);
    init_table(inp, len);
    fill_table(inp, len);

    for (int i = 1; i < len - 1; i ++) {
      // na kazdej druhej pozicii musi byt . (nikdy neostane samotny)
      if (i % 2 == 1) {
        out[i] = '.';
      // ak moze ostat sam tak 'o' inak '.'
      } else {
        out[i] = table[0][i-1] == 1 && table[i+1][len-1] == 1 ? 'o' : '.';
      }
    }

    // test ci moze ostat samotny zaciatok alebo koniec
    out[0] = table[1][len-1] == 1 ? 'o' : '.';
    out[len-1] = table[0][len-2] == 1 ? 'o' : '.';

    out[len] = 0;
    printf("%s\n", out);
  }

  return 0;
}