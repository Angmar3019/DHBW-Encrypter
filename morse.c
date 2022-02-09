#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "checkInput.h"

char letters[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char morse[26][5] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

char* convertCharacters(char *text, int mode){
	//iterate over every character in the given string
	//mode: 0 = text to morse, 1 = morse to text
	char *output; //new pointer needed, since length of text =/= length of output
	char textCopy[strlen(text)]; //array to save input as string instead of pointer
	switch(mode){
		case 0: //encrypt
			output = calloc(strlen(text), sizeof(char[6])); //allocate 6 chars for each input-char (longest morse string = 5 + 1 space)
			for(int i = 0; i < strlen(text); i++){ //iterate over every character in input
				char currentChar = *(text+i);
				if(currentChar == ' '){ //add space to output, if input is space
					strcat(output, " ");
				}
				else{
					for(int j = 0; j < 26; j++){ //iterate over every letter in the alphabet
						if(currentChar == letters[j]){ //if the current character = the letter
							strcat(output, morse[j]);  //add the corresponding morse string to the output
							strcat(output, " "); //add space after morse string
						}
					}
				}
			}
			return output;
			break;
		case 1:
			for(int i = 0; i < strlen(text) + 1; i++){ //convert pointer to string
				textCopy[i] = *(text+i);
			}
			output = calloc(strlen(text), sizeof(char)); //allocate 1 char for each input-char


			char delim[] = " "; //part of splitting a string by space
			char *ptr = strtok(textCopy, delim); //part of splitting a string by space

			int n = 0; //external counter for while loop
			while(ptr != NULL){ //part of splitting a string by space
				for(int i = 0; i < 26; i++){
					if(strcmp(morse[i], ptr) == 0){ //if the morse string is real
						*(output + n) = letters[i]; //add the corresponding letter to the output
					}
				}
				n++;
				ptr = strtok(NULL, delim); //part of splitting a string by space
			}
			return output;
			break;

	}
}

char* morseEncrypt(char *text){ //called from menu
	if(checkInput(text, 1)){ //check if input consists of only letters A-Z or a-z and spaces
		for(int i = 0; i < strlen(text); i++){
			text[i] = toupper(text[i]);
		}
		text = convertCharacters(text, 0); //pass input, and mode = 0 (for encryption) to main function
		return text;
	}
	else{
		return NULL;
	}
}
char* morseDecrypt(char *text){ //called from menu
	if(checkInput(text, 2)){
		text = convertCharacters(text, 1); //pass input and mode = 1 (for decryption) to main function
		return text;
	}
	else{
		return NULL; //return a null pointer if text couldn't be decrypted (wrong input, etc.)
	}
}
