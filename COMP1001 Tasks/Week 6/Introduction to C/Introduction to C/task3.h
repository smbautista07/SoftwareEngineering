#pragma once
#include <stdio.h>

void task3()
{
    char name[20];

    printf("\nEnter your name: "); //get input from keyboard

    scanf_s("%19s", name, sizeof(name));

    printf("\nYour name is %s\n", name);
}