#include "stdafx.h"

typedef struct{
    int field1;
    int field2;
    int field3;
} my_struct_here;

my_struct_here global_struct;

int _tmain(int argc, _TCHAR* argv[]){
    global_struct.field1 = 1;
    global_struct.field2 = 2;
    global_struct.field3 = 3;
    return 0;
}