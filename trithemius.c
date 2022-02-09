#include <string.h>

void shiftTrithemiusCharacters(char *text, int mode){
	//iterate over every character in the given string
	for(int i = 0; i < strlen(text); i++){
		//get ASCII code of current character
		int code = *(text+i);
		//encrypt or decrypt
		switch(mode){
			//encrypt
			case 0:
				code += (i % 95); //add value between 0 and 95 to the character's code (adding 96 has the same effect as adding 0, 97 the same as 1 and so on, so values are kept between 0 and 95)
				break;
			//decrypt
			case 1:
				code -= (i % 95); //subtract value between 0 and 95 to the character's code (subtracting 96 has the same effect as subtracting 0, see above)
				break;
		}
		code > 126? code += (-127) + 32 : code; //if the new value is above the defined range, loop back to beginning of the range (only when encrypting)
		code < 32? code -= (-127) + 32 : code; //if the new value is below the defined range, loop back to end of the range (only when decrypting)
		char *strPointer = text + i; //point towards adress of i-th character in the string
		*strPointer = code; //replace original character in memory with newly calculated character
	}
}

void trithemiusEncrypt(char *text){ //called from menu
	shiftTrithemiusCharacters(text, 0); //pass input and mode = 0 (for encryption) to main function
}
void trithemiusDecrypt(char *text){ //called from menu
	shiftTrithemiusCharacters(text, 1); //pass input and mode = 1 (for decryption) to main function
}
