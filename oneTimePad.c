#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void shiftCharacters(char *text, char *keyText, int mode){
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
				code += keyCode; //add key to shift letters forwards
				break;
			//decrypt
			case 1:
				code -= keyCode; //subtract key to shift letters backwards
				break;
		}
		code > 126? code += (-127) + 32 : code; //if the new value is above the defined range, loop back to beginning of the range (only when encrypting)
		code < 32? code -= (-127) + 32 : code; //if the new value is below the defined range, loop back to end of the range (only when decrypting)
		char *strPointer = text + i; //point towards adress of i-th character in the string
		*strPointer = code; //replace original character in memory with newly calculated character
	}
}

char* createKey(int length){
	char *keyText;
	keyText = calloc(length, sizeof(char)); //allocate enough space to save the key string
	for(int i = 0; i < length; i++){
		keyText[i] = (int) ((double)(95 * rand() / RAND_MAX)); //create a random number between 0 and 95
	}
	return keyText;
}

char* otpEncryptTextOnly(char *text){ //called from menu if key was not provided by user
	srand(time(NULL)); //set seed of rand() to a random seed
	char *key = createKey(strlen(text)); //create a key with the same length as the text
	shiftCharacters(text,key, 0); //pass input, key and mode = 0 (for encryption) to main function
	return key; //return key to user
}

void otpEncrypt(char *text, char *keyText){ //called from menu if key was provided by user
	shiftCharacters(text, keyText, 0); //pass input, key and mode = 0 (for encryption) to main function
}

void otpDecrypt(char *text, char *keyText){ //called from menu
	shiftCharacters(text, keyText, 1); //pass input, key and mode = 1 (for decryption) to main function
}