void menu_home (int state) {
	
	char var[3][100] = {
		"║         »Encrypt«                  Decrypt                      Exit          ║",
		"║          Encrypt                  »Decrypt«                     Exit          ║",
		"║          Encrypt                   Decrypt                     »Exit«         ║",
	};
	
	menu_clear();

	menu_header();
	menu_line(5);
	printf("%s\n", var[state]);
	menu_line(3);
	menu_footer();

	int input;
	input = navigation();
		
	if (input == 1) {
		if (state == 0) {
			state = 2;
			menu_home(state);
		}
		else if (state == 1) {
			state = 0;
			menu_home(state);
		}
		else if (state == 2) {
			state = 1	;
			menu_home(state);
		}
	}
	else if (input == 2){
		if (state == 0) {
			state = 1;
			menu_home(state);
		}
		else if (state == 1) {
			state = 2;
			menu_home(state);

		}
		else if (state == 2) {
			state = 0;
			menu_home(state);
		}
	}
	else if (input == 0) {
		printf("You choosed %d", state);	
	}
}
