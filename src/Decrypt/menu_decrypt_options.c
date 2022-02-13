#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

#include "menu_decrypt_input.h"
#include "menu_decrypt_output.h"

void options_list (int state, int checked) {
    
    char option[1][100] = {
       "Create a checksum file for the undecrypted text                     ║",
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
            menu_line(3);
            printf("%s\n", navigation[0]);
            break;
        
        case 2:
            printf("%s%s\n", box_unchecked, option[0]);
            menu_line(3);
            printf("%s\n", navigation[1]);
            break;

        case 3:
            printf("%s%s\n", box_unchecked, option[0]);
            menu_line(3);
            printf("%s\n", navigation[2]);
            break;
        }
    } else if (checked == 1) {  //A checksum will be generated
        switch (state)
        {
        case 1:
            printf("%s%s\n", box_checked_sel, option[0]);
            menu_line(3);
            printf("%s\n", navigation[0]);
            break;
        
        case 2:
            printf("%s%s\n", box_checked, option[0]);
            menu_line(3);
            printf("%s\n", navigation[1]);
            break;

        case 3:
            printf("%s%s\n", box_checked, option[0]);
            menu_line(3);
            printf("%s\n", navigation[2]);
            break;
        }
    }
}

void menu_decrypt_options (int state, int checked) {

    menu_clear();

    menu_header();
    menu_tab(3);

    menu_line(1);
    options_list(state,checked);
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