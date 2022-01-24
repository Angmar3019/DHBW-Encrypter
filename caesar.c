#include <string.h>

void shiftCharacters(char *text, int key, int mode){
	//iterate over every character in the given string
	for(int i = 0; i < strlen(text); i++){
		//get ASCII code of current character
		int code = *(text+i);
		//keep key in range between 0 and 95 (key = 96 and key = 0 have the same effect, key = 97 = 1, and so on)
		key %= 95;
		//encrypt or decrypt
		switch(mode){
			//encrypt
			case 0:
				code += key; //add key to shift letters forwards
				break;
			//decrypt
			case 1:
				code -= key; //subtract key to shift letters backwards
				break;
		}
		code > 126? code += (-127) + 32 : code; //if the new value is above the defined range, loop back to beginning of the range (only when encrypting)
		code < 32? code -= (-127) + 32 : code; //if the new value is below the defined range, loop back to end of the range (only when decrypting)
		char *strPointer = text + i; //point towards adress of i-th character in the string
		*strPointer = code; //replace original character in memory with newly calculated character
	}
}

void caesarEncrypt(char *text, int key){ //called from menu
	shiftCharacters(text, key, 0); //pass input, key and mode = 0 (for encryption) to main function
}
void caesarDecrypt(char *text, int key){ //called from menu
	shiftCharacters(text, key, 1); //pass input, key and mode = 1 (for decryption) to main function
}
