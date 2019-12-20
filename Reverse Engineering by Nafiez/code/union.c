#include "stdafx.h"

typedef union{
    int my_int;
    char my_char;
} my_union_here;

my_union_here global_union;

int _tmain(int argc, _TCHAR* argv[]){
    my_union_here.my_char = 'a';
    my_union_here.my_int = 123456;
    return 0;
}
