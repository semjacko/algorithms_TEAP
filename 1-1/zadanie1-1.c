// uloha1-1.c -- Róbert Jačko, 17.2.2021 08:31

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long sucet(int pole[], int n){
	long sum = 0;
	for(int i = 0; i < n; i++){
		sum += pole[i];
	}
	return sum;
}

void vymen(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int najdi_Kty(int pole[], int n, int pivotIndex){
	vymen(&pole[pivotIndex], &pole[n-1]);
	int j = 0;
	for(int i = 0; i < n-1; i++){
		if(pole[i] >= pole[n-1]){
			vymen(&pole[j], &pole[i]);
			j++;
		}
	}
	vymen(&pole[j], &pole[n-1]);
	return j;
}

// urci sucet k najvacsich cisel z cisel cena[0],...,cena[n-1]
long sucet_k_najvacsich(int pole[], int n, int k) {
	if (k == n)
		return sucet(pole, n);
	if (k <= 0)
		return 0;
		
	int r = najdi_Kty(pole, n, n-1);;
	while (k != r ) {
		if (k < r){
			int i = r;
			while (pole[i] == pole[r]) {
				if (i == k)
					return sucet(pole, i);
				i--;
			}
			r = i;
			r = najdi_Kty(pole, n, r);
		}
		else
			r = najdi_Kty(pole, n, r+1);
	}
	return sucet(pole, k);
}

int main(void)
{
  // tu si mozete nieco testovat
  int n, k, m, *h;

  while (scanf("%d %d %d", &n, &k, &m) > 0) {
    h = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
      scanf("%d", &h[i]);
    }
    bool safe = sucet_k_najvacsich(h, m, k) <= n;
    printf("%s\n", safe ? "Ano" : "Nie");
  }
  return 0;
}