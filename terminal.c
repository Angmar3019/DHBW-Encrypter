//Libarys
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>        //Required for SHA256 (gcc -lssl -lcrypto)
#include "getch.h"              //Required for Keyboard Input
#include "sha256.h"             //Required for calculating SHA256SUM 
#include "navigation.h"

//Menu - Core functions of the menu and the home menu
#include "menu_core.h"
#include "menu_home.h"

//Encrypt - Each step is divided into a single c-file
#include "menu_encrypt_algo.h"
#include "menu_encrypt_input.h"
#include "menu_encrypt_options.h"
#include "menu_encrypt_output.h"
#include "menu_encrypt.h"

//Decrypt - Each step is divided into a single c-file
#include "menu_decrypt_algo.h"
#include "menu_decrypt_input.h"
#include "menu_decrypt_options.h"
#include "menu_decrypt_output.h"
#include "menu_decrypt.h"

//Algorithm - Algorithm that are available for the encryption and decryption process
#include "checkInput.h"
#include "caesar.h"
#include "morse.h"
#include "oneTimePad.h"
#include "trithemius.h"
#include "vigenere.h"

//Gloabal variables
int global_algo = 1;        //Selected algorithm
int global_method = 1;      //selected method for entering the text
int global_options = 0;     //Option to generate a checksum from the input
int global_output = 1;

#define STRING 4096
char global_text[STRING];   //Input text

char global_checksum[100];  //Checksum

//Main function
int main(){
    
    menu_home(1); //Call the main menu

}




