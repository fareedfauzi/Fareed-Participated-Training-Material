// variables.cpp
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>

int main() {

	char filename[15] = { 0 };
	FILE* fin;
	FILE* fout;

	printf("Enter the filename to be opened: \n");
	scanf("%s", filename);

	/*  open the file for reading */
	fin = fopen(filename, "rb");
	if (fin) {
		fseek(fin, 0, SEEK_END); // seek to end of file
		long size = ftell(fin); // get current file pointer
		fseek(fin, 0, SEEK_SET); // seek back to beginning of file

		char* memory = (char*)malloc(size);
		fread(memory, 1, size, fin);

		printf("[*] Decrypting your file... \n");

		for (int i = 0; i < size; i++) {
			memory[i] = memory[i] ^ 0xFF;
		}

		fout = fopen("encrypted.txt", "wb");
		fwrite(memory, 1, size, fout);
		printf("[*] File encrypted! \n");

		fclose(fin);
		fclose(fout);
		system("pause");
	}
	else {
		printf("We can't find your specified file. Sorry! \n");
		system("pause");
	}

	return 0;
}
