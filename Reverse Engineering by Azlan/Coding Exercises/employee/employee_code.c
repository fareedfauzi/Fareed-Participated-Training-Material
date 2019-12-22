// employee.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    typedef struct _FILE_HEADER {
    public:
        char MAGIC[4]; //"DATA"
        int NumberOfRecords;
    }FILE_HEADER, *PointerFILE_HEADER;

    typedef struct _EMPLOYEE {
    public:
        char name[40];
        int age;
        int salary;
    } EMPLOYEE, *PointerEMPLOYEE;

    FILE *filekita;
    unsigned long fileLen;

   
    // Open employee.db
    filekita = fopen("employee.db", "r");
    if (filekita == NULL) {
        printf("\nCan't open file or file doesn't exist.");

        exit(0);
    }

    //Get file length
    fseek(filekita, 0, SEEK_END);
    fileLen = ftell(filekita);
    fseek(filekita, 0, SEEK_SET);

    //memory allocation
    char *mem = (char *)malloc(fileLen); 
    printf("Address of mem: 0x%x", mem);
    
    // Read for file employee.db and parse the contents
    fread(mem, fileLen, 1, filekita);
    
    /* I'm stuck here */

    //Data written to output2.txt
    FILE* fout = fopen("output2.txt", "wb");
    fwrite(mem, fileLen, 1, fout);
    printf("\nWritten sucessfully.\n");

    fclose(filekita);
    fclose(fout);
    system("pause");


    return 0;


}
