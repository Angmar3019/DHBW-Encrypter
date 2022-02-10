#include <string.h>
#include "checkInput.h"

void shiftVigenereCharacters(char *text, char *key, int mode){
	char keyStr[strlen(text)];
	for(int i = 0; i < strlen(text);i++){
		keyStr[i] = *(key+(i % strlen(key)));
	}
	//iterate over every character in the given string
	for(int i = 0; i < strlen(text); i++){
		//get ASCII code of current character
		int code = *(text+i);
		int keyCode = keyStr[i];
		//encrypt or decrypt
		switch(mode){
			//encrypt
			case 0:
				code += (keyCode - 32); //add value between 0 and 95 to the character's code (adding 96 has the same effect as adding 0, 97 the same as 1 and so on, so values are kept between 0 and 95)
				//printf("Code: %d Keycode: %d\n", code, keyCode);
				break;
			//decrypt
			case 1:
				code -= (keyCode - 32); //subtract value between 0 and 95 to the character's code (subtracting 96 has the same effect as subtracting 0, see above)
				break;
		}
		code > 126? code += (-127) + 32 : code; //if the new value is above the defined range, loop back to beginning of the range (only when encrypting)
		code < 32? code -= (-127) + 32 : code; //if the new value is below the defined range, loop back to end of the range (only when decrypting)
		char *strPointer = text + i; //point towards adress of i-th character in the string
		*strPointer = code; //replace original character in memory with newly calculated character
	}
}

char* vigenereEncrypt(char *text, char *key){ //called from menu
	if(checkInput(text ,0) && checkInput(key, 0)){
		shiftVigenereCharacters(text, key, 0); //pass input and mode = 0 (for encryption) to main function
		return text;
	}
	else{
		return NULL;
	}
}

char* vigenereDecrypt(char *text, char *key){ //called from menu
	if(checkInput(text ,0) && checkInput(key,0)){
		shiftVigenereCharacters(text, key, 1); //pass input and mode = 0 (for encryption) to main function
		return text;
	}
	else{
		return NULL;
	}
}
