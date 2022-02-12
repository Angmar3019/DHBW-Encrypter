/*
getch() by Angmar3019
https://github.com/Angmar3019/getch

A simple version of getch() for C without the use of conio.h.
The code is based on the example of [Kermi3](https://cboard.cprogramming.com/faq-board/27714-faq-there-getch-conio-equivalent-linux-unix.html?highlight=mygetch).
It has been modified so that it is possible to use getch on Windows and Linux at the same time. (On MacOs it should also work, but I don't have a device to test it).

Usage:

1. Download getch.h and move the file into your project folder
2. Add the header file to your main program with include "getch.h
3. After that you can call the function as usual with getch()
*/

#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32 // Windows
    #include <conio.h>
#endif
#ifdef __unix__ //Unix/Linux
    #include <termios.h>

    int getch( ) {
	  struct termios oldt,
	                 newt;
	  int ch;
	  tcgetattr( STDIN_FILENO, &oldt );
	  newt = oldt;
	  newt.c_lflag &= ~( ICANON | ECHO );
	  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	  ch = getchar();		
	  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	  return ch;
	}
#endif
