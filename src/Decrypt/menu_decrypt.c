#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"
#include "sha256.h"

#include "menu_decrypt_algo.h"
#include "menu_decrypt_output.h"
#include "menu_decrypt_input.h"
#include "checkInput.h"

#include "checkInput.h"
#include "caesar.h"
#include "morse.h"
#include "oneTimePad.h"
#include "trithemius.h"
#include "vigenere.h"

int extern global_algo;
int extern global_method;
int extern global_options;
int extern global_output;

#define STRING 4096
char extern global_text[STRING];
char extern global_checksum[100];

char decrypt_key[STRING];
char decrypted[STRING];

void menu_decrypt() {
    menu_decrypt_algo(1, global_algo);
}

void decrypt_print(char *output) {
    if (global_options == 1)
    {
        char extern global_checksum[];

        char temp[100];

        strcpy(temp, global_checksum);

        calcSHA256(output);

        if (strcmp(temp, global_checksum) == 0) { 
            menu_clear();

            menu_header();
            menu_tab(4);
            menu_line(1);
            printf("║ The checksums of the contents match                                           ║\n");
            menu_line(1);
            printf("║                              Press S to continue                              ║\n");
            menu_line(1);
            menu_footer();

            int input;
            input = navigation();

        } else {
            menu_clear();

            menu_header();
            menu_tab(4);
            menu_line(1);
            printf("║ The checksums of the contents don't match. Cancelling the process!            ║\n");
            menu_line(1);
            printf("║                              Press S to continue                              ║\n");
            menu_line(1);
            menu_footer();

            int input;
            input = navigation();

            menu_decrypt_input(1,1);
        }
    }

    switch (global_output)
    {
    case 1:
        menu_clear();

        menu_header();
        menu_tab(4);
        printf("║ The decrypted message is:                                                     ║\n");
        menu_line(1);
        printf("\n");
        printf("%s\n", output);
        printf("\n");
        menu_line(1);
        printf("║                              Press S to continue                              ║\n");
        menu_line(1);
        menu_footer();

        int input;
        input = navigation();

        if (input != 0) //Enter
        {
            decrypt_print(global_text);
        }
        break;
    
    case 2:
        FILE *file_output;
    
        file_output = fopen("decryptet_message.txt", "w"); //Creat decryptet_message.txt file

        if(file_output == NULL) //Abort if file is not created
            {
                printf("Unable to create file.\n");
                exit(EXIT_FAILURE);
            }

        fputs(output, file_output);
        fclose(file_output);

                menu_clear();

        menu_header();
        menu_tab(4);
        menu_line(1);
        printf("║ The encrypted message was written to the file decryptet_message.txt           ║\n");
        menu_line(4);
        printf("║                              Press S to continue                              ║\n");
        menu_line(1);
        menu_footer();

        input = navigation();
        break;
    }
}

void menu_decrypt_error() {
    menu_clear();

    menu_header();
    menu_tab(4);
    menu_line(1);
    printf("║ Error: Unable to decrypt the content                                          ║\n");
    menu_line(1);
    printf("║                              Press S to continue                              ║\n");
    menu_line(1);
    menu_footer();

    int input;
	input = navigation();

    if (input == 0) //Enter
    {
        menu_decrypt_input(1,1);
    } else {
        menu_decrypt_error();
    }
}

void decrypt() {
        menu_clear();

        menu_header();
        menu_tab(4);

        menu_line(1);

        switch (global_algo)
        {
        case 1: //Caesar 
            printf("║ Please enter the key to decrypt the content. The key should only contain the  ║\n");
            printf("║ characters 0-9.                                                               ║\n");
            menu_line(1);
            menu_footer_open();
            printf("║ Please enter a key                                                            ║\n");
            scanf("%s", decrypt_key);
            if (checkNumbers(decrypt_key) == false) {   //Checks if the key consists only of numbers
                menu_decrypt_output(1, global_output);
            }
            int temp;
            temp = atoi(decrypt_key); //Convert char to int

            decrypt_print(caesarDecrypt(global_text, temp));

            break;
        
        case 2: //Morse 
            if (morseDecrypt(global_text) != NULL) {
                decrypt_print(morseDecrypt(global_text));

            } else {
                menu_decrypt_error();
            }
            break;

        case 3: //Trithemius  
            if (trithemiusDecrypt(global_text) != NULL) {
                decrypt_print(trithemiusDecrypt(global_text));

            } else {
                menu_decrypt_error();
            }
            break;

        case 4: //Vigenere
            printf("║ Please enter the key to decrypt the content. The key should only contain the  ║\n");
            printf("║ keys on the keyboard (ASCII Characters between 32 - 126).                     ║\n");
            menu_line(3);
            menu_footer_open();
            printf("║ Please enter a key                                                            ║\n");
            scanf("%s", decrypt_key);
            if (checkASCII(decrypt_key) == false) {  //Only accept the printable ASCII characters (codes 32 to 126)
                menu_decrypt_output(1, global_output);

            } else if (vigenereDecrypt(global_text, decrypt_key) != NULL) {
                decrypt_print(vigenereDecrypt(global_text, decrypt_key));

            } else {
                menu_decrypt_error();
            }
            break;

        case 5: //OneTimePad
            printf("║ Please enter the key to decrypt the content. The key should only contain the  ║\n");
            printf("║ keys on the keyboard (ASCII Characters between 32 - 126).                     ║\n");
            menu_line(3);
            menu_footer_open();
            printf("║ Please enter a key                                                            ║\n");
            scanf("%s", decrypt_key);

            if (checkASCII(decrypt_key) == false) {  //Only accept the printable ASCII characters (codes 32 to 126)
                menu_decrypt_output(1, global_output);

            } else if (otpDecrypt(global_text, decrypt_key) != NULL) {
                decrypt_print(otpDecrypt(global_text, decrypt_key));

            } else {
                menu_decrypt_error();
            }
            break;   
        }
        menu_home(1);
}