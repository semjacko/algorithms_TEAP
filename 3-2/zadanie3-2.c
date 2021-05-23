// uloha3-2.c -- Róbert Jačko, 1.3.2021 20:18

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
  bool end;
  struct NODE *zero;
  struct NODE *one;
} NODE;

void handleAdd(NODE **child) {
  if (*child == NULL) {
    *child = malloc(sizeof(NODE));
    (*child)->end = false;
    (*child)->zero = (*child)->one = NULL;
  }
}

// 5 na 22
void addToTree(NODE *root, unsigned long number) {
  unsigned long curr = number;
  NODE *currNode = root;
  while (curr > 0) {
    int value = curr & 1;
    curr = curr >> 1;
    if (value == 1) {
      handleAdd(&currNode->one);
      currNode = currNode->one;
    } else {
      handleAdd(&currNode->zero);
      currNode = currNode->zero;
    }
  }
  currNode->end = true;
}

int findNextIndex(int *numbers, int len, int current) {
  for (int i = len - 1; i >= 0; i--) {
    if (numbers[i] == current) {
      return i;
    }
  }
  return -1;
}

int main()
{
  unsigned long number = 1;
  NODE root;
  root.end = 0;
  root.zero = root.one = NULL;

  // create tree
  for (int i = 0; i < 22; i++) {
    addToTree(&root, number);
    number *= 5;
  }

  char binary[51];

  while (scanf("%s", binary) > 0) {
    int counters[51] = { 0 };
    int i = strlen(binary) - 1;
    NODE *curr = &root;
    int curr_counter = 1;
    int label = 1;
    
    while (true) {
      curr = binary[i] == '0' ? curr->zero : curr->one;
      
      if (curr == NULL || i == -1) {
        curr = &root;
        i = findNextIndex(counters, strlen(binary), curr_counter);
        if (i == -1) {
          curr_counter++;
          i = findNextIndex(counters, strlen(binary), curr_counter);
        }
        if (i == -1) {
          counters[0] = -1;
          break; 
        }
        label = counters[i] + 1;
        counters[i] = -1;
      }
      
      if (curr->end == 1 && counters[i] == 0) {
        counters[i] = label;
        if (i == 0) {
          break;
        }
      }
      
      i--;

      
    }

    printf("%d\n", counters[0]);
  }



  return 0;
}