// employee.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct _FILE_HEADER {
    char MAGIC[4]; //"DATA"
    int NumberOfRecords;
} FILE_HEADER, * PointerFILE_HEADER;

typedef struct _EMPLOYEE {
    char name[40]; // 40
    int age; // 4
    int salary; // 4, total = 48
} EMPLOYEE, * PointerEMPLOYEE;


int main()
{
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
    
    // Read for file employee.db
    fread(mem, 1, fileLen, filekita); // filekita = file handle
    
    PointerFILE_HEADER pfile_header = (PointerFILE_HEADER) mem;
    
    //printf("num of employees : %d\n", pfile_header->NumberOfRecords);
    
    printf("No of record: %d\n", pfile_header->NumberOfRecords);

    for (int i = 0; i < pfile_header->NumberOfRecords; i++)
    {
        char* ptr_to_beginning_of_employee = (char*)mem + sizeof(FILE_HEADER);
        EMPLOYEE *each = (EMPLOYEE *)ptr_to_beginning_of_employee + i;
        
        //PointerEMPLOYEE* each_employee = (PointerEMPLOYEE*)(mem + sizeof(FILE_HEADER));
        printf("\nName = %s\n", each->name);
        printf("Age = %d\n", each->age);
        printf("Salary = %d\n", each->salary);

        
    }

    //Data written to output2.txt
    /*
    FILE* fout = fopen("output2.txt", "wb");
    fwrite(mem, 1, fileLen, fout);
    printf("\nWritten sucessfully.\n");

    fclose(filekita);
    fclose(fout); 
    */
    system("pause");


    return 0;


}
