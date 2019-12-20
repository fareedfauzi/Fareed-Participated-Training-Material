#include "stdafx.h"

#define SIZE_ARRAY  0xFF
int global_array[SIZE_ARRAY];

int _tmain(int argc, _TCHAR* argv[]){
    int init = 3;
    int i;

    for(i = 0; i < SIZE_ARRAY; i++){
        global_array[i] = init;
    }
    return 0;
}