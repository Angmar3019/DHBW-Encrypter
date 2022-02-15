#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

#include "menu_encrypt_algo.h"
#include "menu_encrypt_input.h"
#include "menu_encrypt_options.h"

void method_list_encrypt (int state, int checked) {

    char method_encrypt[3][100] = {
       "Manual Input                                                        ║",
       "File (In the same directory)                                        ║",
       "Path                                                                ║",
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

    int input_opt = 3;  //Number of input options available for selection
    int line = 0;
    int diff;

    state_before = state - 1;               //Calculates the number of boxes before the selected one
    state_after = input_opt - state;        //Calculates the number of boxes after the selected one

    checked_before = checked - 1;           //Calculates the number of boxes before the checked one
    checked_after = input_opt - checked;    //Calculates the number of boxes after the checked one

    if (state == checked) {     //Case that the state is in the same position as checked
        for (int i = 0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }
        printf("%s%s\n",box_checked_sel, method_encrypt[line]);
        line++;

        for (int i = 0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        menu_line(3);
        printf("%s\n", navigation[0]);

    } else if (state > input_opt){  //Case that "back" or "next" were selected
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, method_encrypt[line]);
        line++;

        for (int i=0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        if (state == input_opt + 1) {
            menu_line(3);
            printf("%s\n", navigation[1]);
        } else if (state == input_opt + 2) {
            menu_line(3);
            printf("%s\n", navigation[2]);
        }

    } else if (state_before < checked_before) {     //Case that state is before checked
        diff = checked_before - state;
        for (int i=0; i< state_before;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }
        printf("%s%s\n",box_unchecked_sel, method_encrypt[line]);
        line++;

        for (int i = 0; i< diff ;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, method_encrypt[line]);
        line++;

        for (int i = 0; i< checked_after;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        menu_line(3);
        printf("%s\n", navigation[0]);

    } else if (state_before > checked_before) {     //Case that checked is before state
        diff = state_before - checked_before;
        for (int i=0; i< checked_before;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_checked, method_encrypt[line]);
        line++;

        for (int i=1; i< diff;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        printf("%s%s\n",box_unchecked_sel, method_encrypt[line]);
        line++;

        for (int i=0; i< state_after;i++) {
            printf("%s%s\n",box_unchecked, method_encrypt[line]);
            line++;
        }

        menu_line(3);
        printf("%s\n", navigation[0]);

    }

}

void input_field_encrypt (int state, int checked) {

    char extern global_text[];

    strcpy(global_text, ""); //Clears the global varibale

    menu_clear();

    menu_header();
    menu_tab(2);

    menu_line(1);
    method_list_encrypt(state,checked);
    menu_line(1);
    menu_footer_open();

    if (checked == 1) { //Manual input - enter the text directly in the terminal
        printf("║ Enter the text you want to encrypt:                                           ║\n");
        scanf("%s", global_text);


    } else {
        switch (checked) //Checks what the condition is and outputs the corresponding message
        {
        case 2: 
            printf("║ Enter the name of the file:                                                   ║\n");
            break;
        
        case 3:
            printf("║ Enter the path of the file:                                                   ║\n");
            break;
        }

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
            menu_line(1);
            printf("║                              Press S to continue                              ║\n");
            menu_line(1);
            menu_footer();

            int input;
            input = navigation();

            menu_encrypt_input(1,1);

        } else {

            str1 = fgetc(fptr);
            while (str1 != EOF)
                {
                    strcat(global_text, pstr);  //Stores the contents of the file in a global variable
                    str1 = fgetc(fptr);
                }

            fclose (fptr);  //Closes the corresponding file

            char *pch = strstr(global_text, "\n"); //Replaces the newline with spaces 
            while(pch != NULL)
            {
                strncpy(pch, " ", 1);
                pch = strstr(global_text, "\n");
            }
        }
    }    
}

void menu_encrypt_input (int state, int checked) {

    menu_clear();

    menu_header();
    menu_tab(2);

    menu_line(1);
    method_list_encrypt(state,checked);
    menu_line(1);
	menu_footer();
    
    int extern global_algo;
    int extern global_method;
    int extern global_options;
    int method_numb = 3;
    int input;
	input = navigation();


    switch (input)
    {
    case 0: //Enter
        if (state <= method_numb) {
            checked = state;
            menu_encrypt_input(state,checked);
            
        } else if (state == 4) {
            global_method = checked;
            menu_encrypt_algo(1, global_algo);

            
        } else if (state == 5) {
            input_field_encrypt(state, checked);
            menu_encrypt_options(1, global_options);
        }

    case 1: //Left
        switch (state)
        {
        case 1:
            state = 5;
            menu_encrypt_input(state,checked);
            break;
        case 2:
            state--;
            menu_encrypt_input(state,checked);
            break;
        case 3:
            state--;
            menu_encrypt_input(state,checked);
            break;
        case 4:
            state--;
            menu_encrypt_input(state,checked);
            break;
        case 5:
            state--;
            menu_encrypt_input(state,checked);
            break;
        }
    case 2: //Right
        switch (state)
        {
        case 1:
            state++;
            menu_encrypt_input(state,checked);
            break;
        case 2:
            state++;
            menu_encrypt_input(state,checked);
            break;
        case 3:
            state++;
            menu_encrypt_input(state,checked);
            break;
        case 4:
            state++;
            menu_encrypt_input(state,checked);
            break;
        case 5:
            state = 1;
            menu_encrypt_input(state,checked);
            break;
        }
    }
}