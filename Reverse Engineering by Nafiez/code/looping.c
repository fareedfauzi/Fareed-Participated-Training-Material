#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]){
    int counter1;

    for(counter1 = 0; counter1 < 10; counter1++){
        printf("FOR-Loop Iteration #%i\n", counter1);
    }

    int counter2 = 0;
    while(counter2 < 10){
        printf("WHILE-Loop Iteration #%i\n", counter2);
    }

    int counter3 = 0;
    do{
        printf("DO-WHILE-Loop Iteration #%i\n", counter3);
    } while(counter3 < 10);

    goto label1;

label1:
    printf("GOTO target\n");

    return 0;
}