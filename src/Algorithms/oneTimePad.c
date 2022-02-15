#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "checkInput.h"

void shiftOTPCharacters(char *text, char *keyText, int mode){
	//iterate over every character in the given string
	for(int i = 0; i < strlen(text); i++){
		//get ASCII code of current character
		int code = *(text+i);
		//get ASCII code of current key character
		int keyCode = *(keyText+i);
		//encrypt or decrypt
		switch(mode){
			//encrypt
			case 0:
				code += (keyCode - 32); //add key to shift letters forwards
				break;
			//decrypt
			case 1:
				code -= (keyCode - 32); //subtract key to shift letters backwards
				break;
		}
		code > 126? code += (-127) + 32 : code; //if the new value is above the defined range, loop back to beginning of the range (only when encrypting)
		code < 32? code -= (-127) + 32 : code; //if the new value is below the defined range, loop back to end of the range (only when decrypting)
		char *strPointer = text + i; //point towards adress of i-th character in the string
		*strPointer = code; //replace original character in memory with newly calculated character
	}
}

char* createKey(int length){
	srand(time(NULL)); //set seed of rand() to a random seed
	char *keyText;
	keyText = calloc(length, sizeof(char)); //allocate enough space to save the key string
	for(int i = 0; i < length; i++){
		int charNum = rand() % 128;
		*(keyText+i) = charNum; //create a random number between 0 and 95
	}
	return keyText;
}

char* otpEncrypt(char *text, char *keyText){ //called from menu if key was provided by user
	if(checkInput(text, 0)){
		shiftOTPCharacters(text, keyText, 0); //pass input, key and mode = 0 (for encryption) to main function
		return text;
	}
	else{
		return NULL;
	}
}

char* otpDecrypt(char *text, char *keyText){ //called from menu
	if(checkInput(text, 0)){
		shiftOTPCharacters(text, keyText, 1); //pass input, key and mode = 1 (for decryption) to main function
		return text;
	}
	else{
		return NULL;
	}
}
