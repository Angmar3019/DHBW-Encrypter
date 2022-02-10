#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "rsa.h"

int validE[] = {0,0,0,0,0,0,0,0,0,0};

int* rsaEncrypt(char* text, int n, int e){
	if(strlen(text) % 2 == 1){
		text = strcat(text, " ");
	}
	int connected[strlen(text) / 2];
	for(int i = 1; i < strlen(text); i += 2){
		printf("1: %c %d\n2:%c %d\nSum: %d\n\n", text[i-1], text[i-1], text[i], text[i], text[i-1] + 127 * text[i]);
		connected[(i-1) / 2] = text[i-1] + 127 * text[i];
	}
	for(int i = 1; i < strlen(text)/2; i++){
		mpz_t bigInt;
		mpz_t eInt;
		mpz_t nInt;
		mpz_t xInt;
		mpz_set_ui(eInt, e);
		mpz_set_ui(nInt, n);
		mpz_set_ui(xInt, connected[i]);
		mpz_powm(bigInt, xInt, eInt, nInt);
		//mpz_out_str(NULL, 10, bigInt);
	}
}

int* rsaCalcE(int p, int q){
	int n0 = (p-1)*(q-1);
	int counter = 2;
	int index = 0;
	while(validE[9] == 0){
		if(GCF(counter, n0) == 1){
			validE[index] = counter;
			index++;
		}
		counter++;
	}
	return validE;
}

int GCF(int x, int y){
	if (y == 0){
      return x;
	}
   	return GCF(y, x % y);
}




int main(){
	char text[] = "Teste";
	char *textPtr = text;

	rsaCalcE(491, 223);
	printf("validE: ");
	for(int i = 0; i < 10; i ++){
		printf("%d ", validE[i]);
	}
	printf("\n");
	int e = validE[0];
	int n = 491 * 223;
	rsaEncrypt(text, n, e);
	printf("'%s'\n", text);
	return 0;
}