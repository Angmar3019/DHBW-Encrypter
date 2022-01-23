int navigation () {
    int input;
    input = getch();

    if (input == 115) /* Enter = S = 115*/
    {
        return 0;
    }
    else if (input == 97 ) { /*  = A = 97 */
        return 1;
    }
    else if (input == 100) /* Right = D = 100 */
    {
        return 2;
    }

    else { /*Retry */
        printf("Invalid Input, try again!\n");
        navigation();
    }
}