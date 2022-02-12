#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "getch.h"

int navigation () { //Reads keyboard input and returns a specified number for later processing
    int input;
    input = getch(); //Waits for a user input and passes it to the variable input

    if (input == 115) //Enter = S = 115
    {
        return 0;
    }
    else if (input == 97 ) //Left = A = 97
    {
        return 1;
    }
    else if (input == 100) //Right = D = 100
    {
        return 2;
    }
    else //Retry if invalid input is given
    {
        printf("Invalid Input, try again!\n");
        navigation();
    }
}