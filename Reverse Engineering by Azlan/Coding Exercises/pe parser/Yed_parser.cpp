// Yed_parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <winnt.h>

int main(int argc, char** argv)
{
    //char c;
    FILE* fp;
    unsigned long fileLen;

    PIMAGE_DOS_HEADER dos_header;
    PIMAGE_NT_HEADERS32 nt_header;
    PIMAGE_FILE_HEADER file_header;
    PIMAGE_OPTIONAL_HEADER32 optional_header;
    PIMAGE_SECTION_HEADER section_header;
    PIMAGE_DATA_DIRECTORY data_directory;
    PIMAGE_IMPORT_DESCRIPTOR importDescriptor;
    PIMAGE_THUNK_DATA thunk_Data;
    PIMAGE_SECTION_HEADER section_import = {};
    
    // If argument not enough 
    if (argc < 2) {
        printf("Usage : ./yed_parser.exe <filename>");
        exit(0);
    }
    
    // Open file 
    fp = fopen(argv[1], "rb");
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
    dos_header = (PIMAGE_DOS_HEADER)mem; //get the first byte which is for DOS header
    printf("============================\n IMAGE_DOS_HEADER\n============================\n");
    printf("\t\t0x%x\t\t\t e_magic\n", dos_header->e_magic);
    printf("\t\t0x%x\t\t\t e_lfanew\n", dos_header->e_lfanew);


    //Image_NT_Header
    printf("\n============================\n IMAGE_NT_HEADERS\n============================\n");
    nt_header = (PIMAGE_NT_HEADERS)(mem + dos_header->e_lfanew);
    printf("\t\t0x%x\t\t\t Signature\n", nt_header->Signature);

    //Image_File_Header
    printf("\n============================\n IMAGE_FILE_HEADERS\n============================\n");
    file_header = (PIMAGE_FILE_HEADER)(mem + dos_header->e_lfanew + 0x4);
    printf("\t\t0x%x\t\t\t Machine\n", file_header->Machine);
    printf("\t\t%d\t\t\t NumberOfSections\n", file_header->NumberOfSections);
    printf("\t\t0x%x\t\t TimeDateStamp\n", file_header->TimeDateStamp);
    printf("\t\t0x%x\t\t\t PointerToSymbolTable\n", file_header->PointerToSymbolTable);
    printf("\t\t0x%x\t\t\t NumberOfSymbols\n", file_header->NumberOfSymbols);
    printf("\t\t0x%x\t\t\t SizeOfOptionalHeader\n", file_header->SizeOfOptionalHeader);
    printf("\t\t0x%x\t\t\t Characteristics\n", file_header->Characteristics);
    
    //Image_Optional_Header
    printf("\n============================\n IMAGE_OPTIONAL_HEADER\n============================\n");
    optional_header = (PIMAGE_OPTIONAL_HEADER32)(mem + dos_header->e_lfanew + 0x18);
    printf("\t\t0x%x\t\t\t Magic\n", optional_header->Magic);
    printf("\t\t0x%x\t\t\t AddressOfEntryPoint\n", optional_header->AddressOfEntryPoint);
    printf("\t\t0x%x\t\t ImageBase\n", optional_header->ImageBase);
    printf("\t\t0x%x\t\t\t SectionAlignment\n", optional_header->SectionAlignment);
    printf("\t\t0x%x\t\t\t FileAlignment\n", optional_header->FileAlignment);
    printf("\t\t0x%x\t\t\t MajorSubsystemVersion\n", optional_header->MajorSubsystemVersion);
    printf("\t\t0x%x\t\t\t SizeOfImage\n", optional_header->SizeOfImage);
    printf("\t\t0x%x\t\t\t SizeOfHeaders\n", optional_header->SizeOfHeaders);
    printf("\t\t0x%x\t\t\t Subsystem\n", optional_header->Subsystem);
    printf("\t\t0x%x\t\t\t NumberOfRvaAndSizes\n", optional_header->NumberOfRvaAndSizes);

    //Image_Section_Header
    printf("\n============================\n IMAGE_SECTION_HEADER\n============================\n");
    // get offset to the import directory RVA
    DWORD importDirectoryRVA = nt_header->OptionalHeader.DataDirectory[1].VirtualAddress;

    // get offset to first section headeer
    DWORD sectionLocation = (DWORD)nt_header + sizeof(DWORD) + (DWORD)(sizeof(IMAGE_FILE_HEADER)) + (DWORD)nt_header->FileHeader.SizeOfOptionalHeader;
    DWORD sectionSize = (DWORD)sizeof(IMAGE_SECTION_HEADER);

    int next_section = 0;
    int nsection = nt_header->FileHeader.NumberOfSections;
    
    for (int i = 0; i < nsection; i++) {
        section_header = (PIMAGE_SECTION_HEADER)sectionLocation;
        printf("\t%s\n", section_header->Name);
        printf("\t\t0x%x\t\tVirtual Size\n", section_header->Misc.VirtualSize);
        printf("\t\t0x%x\t\tVirtual Address\n", section_header->VirtualAddress);
        printf("\t\t0x%x\t\tSize Of Raw Data\n", section_header->SizeOfRawData);
        printf("\t\t0x%x\t\tPointer To Raw Data\n", section_header->PointerToRawData);
        printf("\t\t0x%x\t\tPointer To Relocations\n", section_header->PointerToRelocations);
        printf("\t\t0x%x\t\tPointer To Line Numbers\n", section_header->PointerToLinenumbers);
        printf("\t\t0x%x\t\tNumber Of Relocations\n", section_header->NumberOfRelocations);
        printf("\t\t0x%x\t\tNumber Of Line Numbers\n", section_header->NumberOfLinenumbers);
        printf("\t\t0x%x\tCharacteristics\n", section_header->Characteristics);

        // save section that contains import directory table
        if (importDirectoryRVA >= section_header->VirtualAddress && importDirectoryRVA < section_header->VirtualAddress + section_header->Misc.VirtualSize) {
            section_import = section_header;
        }
        
        sectionLocation += sectionSize;
    }

    // DATA_DIRECTORIES
    printf("\n============================\n DATA DIRECTORIES\n============================\n");
    printf("\n");
    printf("Export Directory Address: 0x%x; Size: 0x%x\n", nt_header->OptionalHeader.DataDirectory[0].VirtualAddress, nt_header->OptionalHeader.DataDirectory[0].Size);
    printf("Import Directory Address: 0x%x; Size: 0x%x\n", nt_header->OptionalHeader.DataDirectory[1].VirtualAddress, nt_header->OptionalHeader.DataDirectory[1].Size);

    //Import Table
    printf("\n============================\n IMPORT TABLE\n============================\n");

    
    // get file offset to import table
    DWORD rawOffset = (DWORD)mem + section_import->PointerToRawData;
    

    // get pointer to import descriptor's file offset. 
    
    //Note that the formula for calculating file offset is: 
    //imageBaseAddress + pointerToRawDataOfTheSectionContainingRVAofInterest + (RVAofInterest - SectionContainingRVAofInterest.VirtualAddress)
    importDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(rawOffset + (nt_header->OptionalHeader.DataDirectory[1].VirtualAddress - section_import->VirtualAddress));
    
    for (; importDescriptor->Name != 0; importDescriptor++) {
        // imported dll modules name
        printf("\t%s\n", rawOffset + (importDescriptor->Name - section_import->VirtualAddress));
        DWORD thunk = importDescriptor->OriginalFirstThunk == 0 ? importDescriptor->FirstThunk : importDescriptor->OriginalFirstThunk;
        thunk_Data = (PIMAGE_THUNK_DATA)(rawOffset + (thunk - section_import->VirtualAddress));

        // dll exported functions
        for (; thunk_Data->u1.AddressOfData != 0; thunk_Data++) {
                printf("\t\t\t\t%s\n", (rawOffset + (thunk_Data->u1.AddressOfData - section_import->VirtualAddress + 2)));
            
        }

    }
    
    free(mem);
    return 0;

}
