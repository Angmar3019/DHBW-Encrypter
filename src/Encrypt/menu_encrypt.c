#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "menu_core.h"
#include "menu_home.h"
#include "sha256.h"

#include "menu_encrypt_algo.h"
#include "menu_encrypt_output.h"
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

char encrypt_key[STRING];
char encrypted[STRING];

void menu_encrypt() {
    menu_encrypt_algo(1, global_algo);
}

void encrypt_print(char *output) {
    switch (global_output)
    {
    case 1:
        printf("%s", output);
        break;
    
    case 2:
        FILE *file_output;
    
        file_output = fopen("encryptet_message.txt", "w"); //Creat encryptet_message.txt file

        if(file_output == NULL) //Abort if file is not created
            {
                printf("Unable to create file.\n");
                exit(EXIT_FAILURE);
            }

        fputs(output, file_output);
        fclose(file_output);
        break;
    }
}

void encrypt() {
    FILE *file_checksum;

    switch (global_options) //Check if geneation of a checksum is required
        {
        case 1:
            calcSHA256(global_text);
            file_checksum = fopen("checksum.txt", "w"); //Creat checksum.txt file

            if(file_checksum == NULL) //Abort if file is not created
                {
                    printf("Unable to create file.\n");
                    exit(EXIT_FAILURE);
                }

            fputs(global_checksum, file_checksum);
            fclose(file_checksum);
            break;
        }

        menu_clear();

        menu_header();
        menu_tab(4);

        menu_line(1);

        switch (global_algo)
        {
        case 1: //Caesar 
            printf("║ Please enter a key to encrypt the content. The key should contain the         ║\n");
            printf("║ characters 0-9. Alternatively you can enter none and a key will be generated. ║\n");
            menu_line(1);
            menu_footer_open();
            printf("║ Please enter a key                                                            ║\n");
            scanf("%s", encrypt_key);
            if (checkInput(encrypt_key, 3) == false) {   //Checks if the key consists only of numbers
                menu_encrypt_output(1, global_output);
            }
            int temp;
            temp = atoi(encrypt_key); //Convert char to int

            encrypt_print(caesarEncrypt(global_text, temp));

            break;
        
        case 2: //Morse 

            break;

        case 3: //Trithemius  

            break;

        case 4: //Vifenere

            break;

        case 5: //OneTimePad

            break;   
        }
        exit(0);
        menu_home(1);

}