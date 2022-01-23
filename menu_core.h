void menu_clear() {
      
    #ifdef _WIN32
        system("cls"); /* Windows*/
    #endif
    #ifdef __unix__
        system("clear"); /* Unix/Linux */
    #endif
    #ifdef __APPLE__
        system("clear"); /* Apple */
    #endif

}

void menu_header() {
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                      NAME                                     ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
}

void menu_line(int repeat) {
	int i;
    for (i = repeat; i<=10; i++) {
        printf("║                                                                               ║\n");
    }
}

void menu_footer() {
    printf("╠═══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                  A:  Move left                                ║\n");
    printf("║           [A][S][D]              D:  Move right                               ║\n");
    printf("║                                  S:  Enter                                    ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
}
