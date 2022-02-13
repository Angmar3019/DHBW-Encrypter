#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

#include "menu_encrypt.h"
#include "menu_encrypt_options.h"
#include "sha256.h"

void output_list_encrypt (int state, int checked) {

    char output_encrypt[2][100] = {
       "Output in Terminal                                                  ║",
       "File (In the same directory)                                        ║",
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

    int state_before, state_after, checked_before, checked_after;

    int output_opt = 2;    //Number of algorithms available for selection
    int line = 0;
    int diff;

    state_before = state - 1;               //Calculates the number of boxes before the selected one
    state_after = output_opt - state;       //Calculates the number of boxes after the selected one

    checked_before = checked - 1;           //Calculates the number of boxes beforee the checked one
    checked_after = output_opt - checked;   //Calculates the number of boxes after the checked one

    if (state == checked) {     //Case that the state is in the same position as checked
        for (int i = 0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }
        printf("%s%s\n",box_checked_sel, output_encrypt[line]);
        line++;

        for (int i = 0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    } else if (state > output_opt){     //Case that "back" or "next" were selected
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, output_encrypt[line]);
        line++;

        for (int i=0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        if (state == output_opt + 1) {
            menu_line(1);
            printf("%s\n", navigation[1]);
        } else if (state == output_opt + 2) {
            menu_line(1);
            printf("%s\n", navigation[2]);
        }

    } else if (state_before < checked_before) { //Case that state is before checked
        diff = checked_before - state;
        for (int i=0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }
        printf("%s%s\n",box_unchecked_sel, output_encrypt[line]);
        line++;

        for (int i = 0; i< diff ;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, output_encrypt[line]);
        line++;

        for (int i = 0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    } else if (state_before > checked_before) { //Case that checked is before state
        diff = state_before - checked_before;
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, output_encrypt[line]);
        line++;

        for (int i=1; i< diff;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_unchecked_sel, output_encrypt[line]);
        line++;

        for (int i=0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, output_encrypt[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    }

}

void menu_encrypt_output (int state, int checked) {

    menu_clear();

    menu_header();
    menu_tab(4);

    menu_line(1);
    output_list_encrypt(state,checked);
    menu_line(1);
	menu_footer();
    
    int extern global_algo;
    int extern global_method;
    int extern global_options;
    int extern global_output;
    int output_numb = 2;

    int input;
	input = navigation();

    switch (input)
    {
    case 0: //Enter
        if (state <= output_numb) {
            checked = state;
            menu_encrypt_output(state,checked);
            
        } else if (state == 3) {
            global_output = checked;
            menu_encrypt_options(1, global_options);

            
        } else if (state == 4) {
            global_output = checked;
            encrypt();
        }

    case 1: //Left
        switch (state)
        {
        case 1:
            state = 4;
            menu_encrypt_output(state,checked);
            break;
        case 2:
            state--;
            menu_encrypt_output(state,checked);
            break;
        case 3:
            state--;
            menu_encrypt_output(state,checked);
            break;
        case 4:
            state--;
            menu_encrypt_output(state,checked);
            break;
        }
    case 2: //Right
        switch (state)
        {
        case 1:
            state++;
            menu_encrypt_output(state,checked);
            break;
        case 2:
            state++;
            menu_encrypt_output(state,checked);
            break;
        case 3:
            state++;
            menu_encrypt_output(state,checked);
            break;
        case 4:
            state = 1;
            menu_encrypt_output(state,checked);
            break;
        }
    }
}