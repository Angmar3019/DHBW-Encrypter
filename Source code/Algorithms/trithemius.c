#include <string.h>

void shiftCharacters(char *text, int mode){
	for(int i = 0; i < strlen(text); i++){
		int code = *(text+i);
		switch(mode){
			case 0:
				code += (i % 95);
				break;
			case 1:
				code -= (i % 95);
				break;
		}
		code > 126? code += (-127) + 32 : code;
		char *strPointer = text + i;
		*strPointer = code;
	}
}

void encrypt(char *text){
	shiftCharacters(text, 0);
}
void decrypt(char *text){
	shiftCharacters(text, 1);
}