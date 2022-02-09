#include "checkInput.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


bool checkASCII(char *text){
	bool isAscii = true;
	for(int i = 0; i < strlen(text); i++){ //iterate over every character
		char currentChar = *(text + i);
		if(!(currentChar >= 32 && currentChar <= 126)){ //only accept the printable ASCII characters (codes 32 to 126)
			isAscii = false;
		}
	}
	return isAscii;
}

bool checkAlphabetSpaces(char *text){
	bool isAlphabet = true;
	for(int i = 0; i < strlen(text); i++){ //iterate over every character
		char currentChar = *(text + i);
		if(!((currentChar >= 65 && currentChar <= 90 || currentChar >= 97 && currentChar <= 122))){ //only accept lowercase letters, uppercase letters and spaces
			if(currentChar != 32){
				isAlphabet = false;
			}
		}
	}
	return isAlphabet;
}

bool checkMorse(char *text){
	char textCopy[strlen(text)];
	for(int i = 0; i < strlen(text) + 1; i++){
		textCopy[i] = *(text+i);
	}
	char morse[26][5] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

	bool isMorse = true;
	char delim[] = " ";

	char *ptr = strtok(textCopy, delim);

	//split input string by space and check whether the substrings are real morse strings
	while(ptr != NULL){
		bool isInList = false;
		for(int i = 0; i < 26; i++){
			if(strcmp(morse[i], ptr) == 0){
				isInList = true;
			}
		}
		if(!isInList){
			isMorse = false;
		}
		ptr = strtok(NULL, delim);
	}
	return isMorse;
}

bool checkInput(char *text, int mode){
	//0 = ASCII, 1 = Alphabet, 2 = Morse
	switch(mode){
		case 0:
			return checkASCII(text);
			break;
		case 1:
			return checkAlphabetSpaces(text);
			break;
		case 2:
			return checkMorse(text);
			break;
		default:
			return 0;
			break;
	}
}