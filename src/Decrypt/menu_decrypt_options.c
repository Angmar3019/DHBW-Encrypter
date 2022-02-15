#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

#include "menu_decrypt_input.h"
#include "menu_decrypt_output.h"

void options_list_decrypt (int state, int checked) {
    
    char option[1][100] = {
       "Open a checksum file to verify the integrity of the content.        ║",
    };
    
    char navigation[3][100] = {
    "║   ←  Back                                                           Next  →   ║",
    "║   ← »Back«                                                          Next  →   ║",
    "║   ←  Back                                                          »Next« →   ║",
    };

    char box_unchecked[] =      "║     [ ]   "; 
    char box_unchecked_sel[] =  "║    »[ ]«  "; 
    char box_checked[] =        "║     [X]   "; 
    char box_checked_sel[] =    "║    »[X]«  "; 

    if (checked == 0) { //A checksum will not be generated
        switch (state)
        {
        case 1:
            printf("%s%s\n", box_unchecked_sel, option[0]);
            menu_line(5);
            printf("%s\n", navigation[0]);
            break;
        
        case 2:
            printf("%s%s\n", box_unchecked, option[0]);
            menu_line(5);
            printf("%s\n", navigation[1]);
            break;

        case 3:
            printf("%s%s\n", box_unchecked, option[0]);
            menu_line(5);
            printf("%s\n", navigation[2]);
            break;
        }
    } else if (checked == 1) {  //A checksum will be generated
        switch (state)
        {
        case 1:
            printf("%s%s\n", box_checked_sel, option[0]);
            menu_line(5);
            printf("%s\n", navigation[0]);
            break;
        
        case 2:
            printf("%s%s\n", box_checked, option[0]);
            menu_line(5);
            printf("%s\n", navigation[1]);
            break;

        case 3:
            printf("%s%s\n", box_checked, option[0]);
            menu_line(5);
            printf("%s\n", navigation[2]);
            break;
        }
    }
}

void input_field_checksum() {

    char extern global_checksum[];

    strcpy(global_checksum, ""); //Clears the global varibale

    menu_clear();

    menu_header();
    menu_tab(2);

    menu_line(1);
    printf("║ Enter the file name of the checksum file. Must be in the same directory.      ║\n");
    menu_line(5);
    menu_footer_open();
    printf("║ Enter the name of the file:                                                   ║\n");

    FILE * fptr;
    char str[100];
    char fname[100];
    char str1;
    char *pstr = &str1;

    scanf("%s", fname); //Reads the name of the file or the path

    fptr = fopen (fname, "r");  //Opens the corresponding file

    if (fptr == NULL)
    {
        menu_clear();
        
        menu_header();
        menu_tab(4);
        menu_line(1);
        printf("║ Error: Unable to open the file.                                               ║\n");
        menu_line(5);
        printf("║                              Press S to continue                              ║\n");
        menu_line(1);
        menu_footer();

        int input;
        input = navigation();

        menu_decrypt_input(1,1);

    } else {

        str1 = fgetc(fptr);
        while (str1 != EOF)
            {
                strcat(global_checksum, pstr);  //Stores the contents of the file in a global variable
                str1 = fgetc(fptr);
            }

        fclose (fptr);  //Closes the corresponding file
    }
}

void menu_decrypt_options (int state, int checked) {

    menu_clear();

    menu_header();
    menu_tab(3);

    menu_line(1);
    options_list_decrypt(state,checked);
    menu_line(1);
	menu_footer();
    
    int extern global_algo;
    int extern global_method;
    int extern global_options;
    int extern global_output;
    int method_numb = 3;
    int input;
	input = navigation();

    switch (input)
    {
    case 0: //Enter
        if (state == 1) {
            switch (checked)
            {
            case 0:
                checked = 1;
                menu_decrypt_options(1, checked);
                break;
            
            case 1:
                checked = 0;
                menu_decrypt_options(1, checked);
                break;
            }

        } else if (state == 2) {
            global_options = checked;
            menu_decrypt_input(1, global_method);

            
        } else if (state == 3) {
            global_options = checked;
            
            if (global_options == 1) {
                input_field_checksum();
            }

            menu_decrypt_output(1, global_output);
        }

    case 1: //Left
        switch (state)
        {
        case 1:
            state = 3;
            menu_decrypt_options(state,checked);
            break;
        case 2:
            state--;
            menu_decrypt_options(state,checked);
            break;
        case 3:
            state--;
            menu_decrypt_options(state,checked);
            break;
        }
    case 2: //Right
        switch (state)
        {
        case 1:
            state++;
            menu_decrypt_options(state,checked);
            break;
        case 2:
            state++;
            menu_decrypt_options(state,checked);
            break;
        case 3:
            state = 1;
            menu_decrypt_options(state,checked);
            break;
        }
    }
}