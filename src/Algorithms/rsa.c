#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "rsa.h"



mpz_t *rsaEncrypt(char* text, int n, int e){
	if(strlen(text) % 2 == 1){
		text = strcat(text, " ");
	}
	mpz_t *output;
	output = calloc(strlen(text)/2+1, sizeof(mpz_t));

	int connected[strlen(text) / 2];
	for(int i = 1; i < strlen(text); i += 2){
		connected[(i-1) / 2] = text[i-1] + 127 * text[i];
	}
	mpz_t amount;
	mpz_init(amount);
	mpz_set_ui(amount, strlen(text)/2);
	mpz_set(output[0], amount);
	for(int i = 1; i < strlen(text)/2 + 1; i++){
		mpz_t bigInt;
		mpz_init(bigInt);

		mpz_t eInt;
		mpz_init(eInt);

		mpz_t nInt;
		mpz_init(nInt);

		mpz_t xInt;
		mpz_init(xInt);


		mpz_set_ui(eInt, e);
		mpz_set_ui(nInt, n);

		mpz_set_ui(xInt, connected[i-1]);

		mpz_powm(bigInt, xInt, eInt, nInt);

		mpz_set(output[i], bigInt);
	}
	return output;
}

char *rsaDecrypt(mpz_t *input, int n, int d){
	unsigned long int *converted;
	converted = malloc(sizeof(unsigned long int) * mpz_get_ui(input[0]));
	for(int i = 1; i < mpz_get_ui(input[0]) + 1; i++){
		mpz_t currChar;
		mpz_init(currChar);
		mpz_set(currChar, input[i]);
		mpz_t nInt;
		mpz_init_set_ui(nInt, n);
		mpz_powm_ui(currChar, currChar, d, nInt);

		unsigned long int currCharInt = mpz_get_ui(currChar);
		*(converted + i - 1) = currCharInt;
	}
	char *splitChars;
	splitChars = calloc(mpz_get_ui(input[0]) * 2, sizeof(char));
	for(int i = 0; i < mpz_get_ui(input[0]); i++){
		unsigned long int currChars = converted[i];
		*(splitChars + 2 * i) = (char)(currChars % 127);
		*(splitChars + 2 * i + 1) = (char)(currChars / 127);
	}
	return splitChars;
}

int* rsaCalcE(int p, int q){
	int *validE;
	validE = calloc(10, sizeof(int));
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

int* rsaCalcD(int n0, int e){
	int *validD;
	validD = calloc(10, sizeof(int));
	int counter = 2;
	int index = 0;
	while(validD[9] == 0){
		if(e * counter % n0 == 1){
			validD[index] = counter;
			index++;
		}
		counter++;
	}
	return validD;
}

int GCF(int x, int y){
	if (y == 0){
      return x;
	}
   	return GCF(y, x % y);
}

int main(){
	char text[] = "Hello";

	char *textPtr = text;
	int p = 491;
	int q = 223;
	int n = p * q;
	int n0 = (p-1)*(q-1);

	int *validE = rsaCalcE(p, q);
	int e = validE[3];
	mpz_t *output = rsaEncrypt(text, n, e);

	int *validD = rsaCalcD(n0, e);
	int d = validD[0];
	char *decryptedOutput = rsaDecrypt(output, n, d);
	return 0;
}