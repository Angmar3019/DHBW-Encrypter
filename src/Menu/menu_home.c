#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_core.h"
#include "menu_home.h"
#include "navigation.h"

void menu_home (int state) { //Main menu of the program
	
	char var[3][100] = { //Three main options in the program
		"║         »Encrypt«                  Decrypt                      Exit          ║",
		"║          Encrypt                  »Decrypt«                     Exit          ║",
		"║          Encrypt                   Decrypt                     »Exit«         ║",
	};
	
	menu_clear();

	//Build the main menu
	menu_header_home();
	menu_line(5);
	printf("%s\n", var[state -1]); //Print the current selected option
	menu_line(3);
	menu_footer();

	//Read the input and process it accordingly
	int input;
	input = navigation();

	switch (input)
    {
    case 0: //Enter
		switch (state)
		{
        case 1:
			menu_encrypt(); //Go to the submenu for encrypting files
            break;
        case 2:
			menu_decrypt(); //Go to the submenu for decrypting files
        case 3:
			menu_clear();	
			exit(0);		//Exit the program
		}
    case 1: //Left
        switch (state)
        {
        case 1:
            state = 3;
			menu_home(state);

        case 2:
            state--;
			menu_home(state);

        case 3:
            state--;
			menu_home(state);

		}
    case 2: //Right
        switch (state)
        {
        case 1:
            state++;
			menu_home(state);

        case 2:
            state++;
			menu_home(state);

        case 3:
            state = 1;
			menu_home(state);

        }
	}
}