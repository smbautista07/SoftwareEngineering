#pragma once
#include <stdio.h> //this library is needed for printf() function
#include <windows.h> //this library is needed for pause() function

void task4() {

    char string[1000];//input string
    char pattern[2]; //pattern string. The first character is the one we need to find in the string array. the second character is always zero as it is the last character of the array
    unsigned int counter = 0;

    printf("\nHi - Enter a large string: ");
    scanf_s("%999s", string, sizeof(string)); //read the string from keyboard

    printf("Enter a character to find its frequency: ");
    scanf_s("%1s", pattern, sizeof(pattern));

    for (int i = 0; string[i] != '\0'; ++i) {
        if (pattern[0] == string[i])
            counter++;
    }

    printf("Frequency of character %c is %d\n\n", pattern[0], counter);

    system("pause"); //this function prevents from closing the output window

}