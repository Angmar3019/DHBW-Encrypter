#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

#include "menu_decrypt_input.h"
#include "menu_decrypt_algo.h"

void algo_list(int state, int checked) {

    char algo[5][100] = {
        "Caesar                                                              ║",
        "Morse                                                               ║",
        "Trithemius                                                          ║",
        "Vigenere                                                            ║",
        "OneTimePad                                                          ║",       
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

    int algo_numb = 5;  //Number of algorithms available for selection
    int line = 0;
    int diff;

    state_before = state - 1;               //Calculates the number of boxes before the selected one
    state_after = algo_numb - state;        //Calculates the number of boxes after the selected one

    checked_before = checked - 1;           //Calculates the number of boxes before the checked one
    checked_after = algo_numb - checked;    //Calculates the number of boxes after the checked one

    if (state == checked) {     //Case that the state is in the same position as checked
        for (int i = 0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }
        printf("%s%s\n",box_checked_sel, algo[line]);
        line++;

        for (int i = 0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    } else if (state > algo_numb){  //Case that "back" or "next" were selected
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        printf("%s%s\n",box_checked, algo[line]);
        line++;

        for (int i=0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        if (state == algo_numb + 1) {
            menu_line(1);
            printf("%s\n", navigation[1]);
        } else if (state == algo_numb + 2) {
            menu_line(1);
            printf("%s\n", navigation[2]);
        }

    } else if (state_before < checked_before) { //Case that state is before checked
        diff = checked_before - state;
        for (int i=0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }
        printf("%s%s\n",box_unchecked_sel, algo[line]);
        line++;

        for (int i = 0; i< diff ;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        printf("%s%s\n",box_checked, algo[line]);
        line++;

        for (int i = 0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    } else if (state_before > checked_before) {   //Case that checked is before state
        diff = state_before - checked_before;
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        printf("%s%s\n",box_checked, algo[line]);
        line++;

        for (int i=1; i< diff;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        printf("%s%s\n",box_unchecked_sel, algo[line]);
        line++;

        for (int i=0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, algo[line]);
            line++;
        }

        menu_line(1);
        printf("%s\n", navigation[0]);

    }

}
  

void menu_decrypt_algo (int state, int checked) {

    menu_clear();

    menu_header();
    menu_tab(1);

    menu_line(1);
    algo_list(state,checked);
    menu_line(1);
	menu_footer();

    int extern global_algo;
    int extern global_method;
    int algo_numb = 5;
    int input;
	input = navigation();


    switch (input)
    {
    case 0: //Enter
        if (state <= algo_numb) {
            checked = state;
            menu_decrypt_algo(state,checked);
            
        } else if (state == 6) {
            global_algo = checked;
            menu_home(1);
            
        } else if (state == 7) {
            global_algo = checked;

            menu_decrypt_input(1,global_method);
        }

    case 1: //Left
        switch (state)
        {
        case 1:
            state = 7;
            menu_decrypt_algo(state,checked);
            break;
        case 2:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        case 3:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        case 4:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        case 5:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        case 6:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        case 7:
            state--;
            menu_decrypt_algo(state,checked);
            break;
        }

    case 2: //Right
        switch (state)
        {
        case 1:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 2:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 3:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 4:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 5:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 6:
            state++;
            menu_decrypt_algo(state,checked);
            break;
        case 7:
            state = 1;
            menu_decrypt_algo(state,checked);
            break;
        }
    }
}