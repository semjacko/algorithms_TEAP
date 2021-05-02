// uloha4-2.c -- Róbert Jačko, 17.3.2021 08:03

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// namapuje pismena: ? => 0  samohl => 1  spoluhl => 2
void map(char word[], int len, int mapping[]) {
  for (int i = 0; i < len; i++) {
    char c = word[i];
    if (c == '?') {
      mapping[i] = 0;
    } else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y') {
      mapping[i] = 1;
    } else {
      mapping[i] = 2;
    }
  }
}

// test ci sa v slove nachadzaju 3 posebe iduce samohlasky alebo 5 spoluhlasok
// '?' sa ignoruje
bool lettersOnly(int mapping[], int len) {
  int last = mapping[0], counter = 1;
  for (int i = 1; i < len; i++) {
    if (mapping[i] == last) {
      counter++;
    } else {
      counter = 1;
      last = mapping[i];
    }
    if ((counter == 3 && last == 1) || (counter == 5 && last == 2)) {
      return true;
    }
  }
  return false;
}

// test ci po dosadeni iba samohlasok alebo iba spoluhlasok bude 3 alebo 5 po sebe iducih
bool maximalize(int mapping[], int len) {
  // dosadzanie samohlasok za otazniky
  int m = mapping[0] != 2 ? 1 : 2;
  int last = m, counter = 1;
  for (int i = 1; i < len; i++) {
    m = mapping[i] != 2 ? 1 : 2;
    if (m == last) {
      counter++;
    } else {
      counter = 1;
      last = m;
    }
    if ((counter == 3 && last == 1) || (counter == 5 && last == 2)) {
      return true;
    }
  }
  // dosadzanie spoluhlasok za otazniky
  m = mapping[0] != 1 ? 2 : 1;
  last = m; 
  counter = 1;
  for (int i = 1; i < len; i++) {
    m = mapping[i] != 1 ? 2 : 1;
    if (m == last) {
      counter++;
    } else {
      counter = 1;
      last = m;
    }
    if ((counter == 3 && last == 1) || (counter == 5 && last == 2)) {
      return true;
    }
  }
  return false;
}

// dosadzanie tak, aby nesli za sebou 3 samohlasky alebo 5 spoluhlasok
bool minimalize(int mapping[], int len) {
  int last = mapping[0], counter = 1;
  for (int i = 1; i < len; i++) {
    if (mapping[i]) { // ak pismenko
      if (mapping[i] == last) {
        counter++;
      } else if (mapping[i] == 0) {
        counter = 1;
        last = mapping[i];
      }
    } else { // ak otaznik
      if (counter == 2 && last == 1) { // ak uz by boli 3 samohlasky
        last = 2;
      } else if (counter == 5 && last == 2) { // ak uz by bolo 5 spoluhlasok
        last = 1;
      } else { // inak nehrozi nic
        last = 0;
      }
        counter = 1;
    }
    if ((counter == 3 && last == 1) || (counter == 5 && last == 2)) {
      return true;
    }
  }
  return false;
}

int main()
{
  // sem napis svoje riesenie
  char word[51];
  int mapping[50];

  while (scanf("%s", word) > 0) {
    int len = strlen(word);
    map(word, len, mapping);
    if (lettersOnly(mapping, len)) {
      printf("paci\n");
    } else if (maximalize(mapping, len)) {
      if (minimalize(mapping, len)) {
        printf("paci\n");
      } else {
        printf("neviem\n");
      }
    } else {
      printf("nepaci\n");
    }
  }

  return 0;
}