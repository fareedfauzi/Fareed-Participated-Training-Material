// Yed_parser.cpp : This file contains the 'main' function. Program execution begins and ends there



//Nih antara library yang kita kena include, terutama sekali winnt.h. Sebab all struct PE ada dalam winnt.h. Windows.h tayah pun takpe bila dah ada winnt.h
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <winnt.h>

//Untuk user pass argument ataupun parameter istilahnya. Contohnya Yed_parser.exe [nama file]. So, nama file tu adalah argument kita.
int main(int argc, char** argv)
{
    //Assign kan fp sebagai datatype FILE. So variable fp akan jadi our file.
    FILE* fp;
    unsigned long fileLen;

    PIMAGE_DOS_HEADER dos_header;
    PIMAGE_NT_HEADERS32 nt_header;
    PIMAGE_FILE_HEADER file_header;
    PIMAGE_OPTIONAL_HEADER32 optional_header;
    PIMAGE_SECTION_HEADER section_header;

    
    /*fp = fopen("POC.exe", "rb");
    if (fp == NULL) {
        printf("\nCan't open file or file doesn't exist.");

        exit(0);
    }
    printf("Welcome... \n \n");*/
    
    
    
    // If argument not enough. Contoh dia supply yed_parser without parameter 
    if (argc < 2) {
        printf("Usage : ./yed_parser.exe <filename>");
        exit(0);
    }
    
    // Open file dalam readbyte(rb). Then iniate ke dalam fp.
    fp = fopen(argv[1], "rb");
    //Kalau file tak jumpa, dia print mesej bawah tu.
    if (fp == NULL) {
        printf("\nCan't open file or file doesn't exist.");
        exit(0);
    }
    
    
    // Determine file length
    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Memory allocation
    char* mem = (char*)malloc(fileLen);

    // Read opened file
    fread(mem, 1, fileLen, fp);

    

    //Image_DOS_Header
    dos_header = (PIMAGE_DOS_HEADER)mem; //get the first byte which is for DOS header. 0x00 byte.
    printf("============================\nIMAGE_DOS_HEADER\n============================\n"); //refer line 16682 in winnt.h
    //Nih member2 struct PIMAGE_DOS_HEADER yang important
    printf("e_magic: %x\n", dos_header->e_magic);
    printf("e_lfanew: %x\n", dos_header->e_lfanew);


    //Image_NT_Header
    printf("\n============================\nIMAGE_NT_HEADERS\n============================\n"); //refer line 16990 in winnt.h
    nt_header = (PIMAGE_NT_HEADERS)(mem + dos_header->e_lfanew); //to get the first byte for NT_HEADER. 1st byte of file (0x00) + value of e_lfanew (x value) = first byte of NT_HEADER
    printf("Signature: %x\n", nt_header->Signature);

    //Image_File_Header
    printf("\n============================\nIMAGE_FILE_HEADERS\n============================\n");
    file_header = (PIMAGE_FILE_HEADER)(mem + dos_header->e_lfanew + 0x4); // mem + dos_header->e_lfanew + 4 = nt_header
    //Why 0x4? refer poster PE header yang abang Lan bagi.
    printf("Machine: %x\n", file_header->Machine);
    printf("NumberOfSections: %d\n", file_header->NumberOfSections);
    printf("TimeDateStamp: %x\n", file_header->TimeDateStamp);
    printf("PointerToSymbolTable: %x\n", file_header->PointerToSymbolTable);
    printf("NumberOfSymbols: %x\n", file_header->NumberOfSymbols);
    printf("SizeOfOptionalHeader: %x\n", file_header->SizeOfOptionalHeader);
    printf("Characteristics: %x\n", file_header->Characteristics);
    
    //Image_Optional_Header
    printf("\n============================\nIMAGE_OPTIONAL_HEADER\n============================\n");
    optional_header = (PIMAGE_OPTIONAL_HEADER32)(mem + dos_header->e_lfanew + 0x18); // mem + dos_header->e_lfanew + 0x18 = optional_header32
    ////Why 0x18? refer poster PE header yang abang Lan bagi.
    printf("Magic: %x\n", optional_header->Magic);
    printf("AddressOfEntryPoint: %x\n", optional_header->AddressOfEntryPoint);
    printf("ImageBase: %llx\n", optional_header->ImageBase);
    printf("SectionAlignment: %x\n", optional_header->SectionAlignment);
    printf("FileAlignment: %x\n", optional_header->FileAlignment);
    printf("MajorSubsystemVersion: 0x%x\n", optional_header->MajorSubsystemVersion);
    printf("SizeOfImage: %x\n", optional_header->SizeOfImage);
    printf("SizeOfHeaders: %x\n", optional_header->SizeOfHeaders);
    printf("Subsystem: %x\n", optional_header->Subsystem);
    printf("NumberOfRvaAndSizes: %x\n", optional_header->NumberOfRvaAndSizes);

    //Image_Section_Header
    printf("\n============================\nIMAGE_SECTION_HEADER\n============================\n");
    
    int next_section = 0;

    int nsection = nt_header->FileHeader.NumberOfSections;
    for (int i = 0; i < nsection; i++) {
        //Why 0xF8? refer poster PE header yang abang Lan bagi. Kira total Image optional header dari awal sampai habis akan dapat F8
        section_header = (PIMAGE_SECTION_HEADER)(mem + dos_header->e_lfanew + 0xF8 + next_section);
        //next section akan tambah dengan 40bytes sbb size of each of section header 40 bytes.
        next_section = next_section + sizeof(IMAGE_SECTION_HEADER);
        printf("\n%s\n", section_header->Name);
        printf("RVA: %x\n", section_header->Misc.VirtualSize);
        printf("Virtual address: %x\n", section_header->VirtualAddress);
        printf("SizeOfRawData: %x\n", section_header->SizeOfRawData);
        printf("PointerToRawData: %x\n", section_header->PointerToRawData);
        printf("PointerToRelocations: %x\n", section_header->PointerToRelocations);
        printf("PointerToLinenumbers: %x\n", section_header->PointerToLinenumbers);
        printf("NumberOfRelocations: %x\n", section_header->NumberOfRelocations);
        printf("Characteristics: %x\n", section_header->Characteristics);
        printf("________________________\n");
        
    };

    free(mem);
    return 0;
}
