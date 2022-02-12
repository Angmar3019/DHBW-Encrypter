#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu_clear() { //Clean terminal with the command for the specific operating system
      
    #ifdef _WIN32
        system("cls"); //Windows
    #endif
    #ifdef __unix__
        system("clear"); //Unix/Linux
    #endif
    #ifdef __APPLE__
        system("clear"); //Apple
    #endif

}

void menu_header_home() { //Menu header for the main menu
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                      NAME                                     ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
}

void menu_header() { //Menu header for the submenus encrypt/decrypt
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                      NAME                                     ║\n");
    printf("╠═════════════════════╦═════════════════╦═══════════════════╦═══════════════════╣\n");         
}

void menu_tab_encrypt(int state) { //Different progress in encrypt/decrypt submenus
    state--;
	char tab_encrypt[4][100] = {
		"║     »Algorithm«     ║      Input      ║      Options      ║       Output      ║",
		"║      Algorithm      ║     »Input«     ║      Options      ║       Output      ║",
        "║      Algorithm      ║      Input      ║     »Options«     ║       Output      ║",
        "║      Algorithm      ║      Input      ║      Options      ║      »Output«     ║",
	};
    printf("%s\n", tab_encrypt[state]);
    printf("╠═════════════════════╩═════════════════╩═══════════════════╩═══════════════════╣\n");

}

void menu_line(int repeat) { //Print empty lines according to the given input
	int i;
    for (i = 0; i<repeat; i++) {
        printf("║                                                                               ║\n");
    }
}

void menu_footer() { //End of the menu with the controls
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                  A:  Move left                                ║\n");
    printf("║           [A][S][D]              D:  Move right                               ║\n");
    printf("║                                  S:  Enter                                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
}

void menu_footer_open() { //End of the menu with the controls and extension for user inputs
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                  A:  Move left                                ║\n");
    printf("║           [A][S][D]              D:  Move right                               ║\n");
    printf("║                                  S:  Enter                                    ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
}