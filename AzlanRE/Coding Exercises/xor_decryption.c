// variables.cpp
#include <cstdio>
#include <cstdlib>

int main() {

	char filename[100] = { 0 };
	FILE* fin;
	FILE* fout;

	printf("Enter the filename (full path) to be opened: \n");
	scanf("%s", filename);
	

	/*  open the file for reading */
	fin = fopen(filename, "rb");
	if (fin) {
		fseek(fin, 0, SEEK_END); // seek to end of file
		long size = ftell(fin); // get current file pointer
		fseek(fin, 0, SEEK_SET); // seek back to beginning of file

		char* memory = (char*)malloc(size);
		fread(memory, 1, size, fin);


		printf("[*] Searh for your encrypted file... \n");
		printf("[*] The decryption key is 0xFF \n");

		for (int i = 0; i < size; i++) {
			memory[i] = memory[i] ^ 0xFF;
		}

		printf("[*] Decrypting for your encrypted file... \n");

		fout = fopen("decrypted.txt", "wb");
		fwrite(memory, 1, size, fout);

		fclose(fin);
		fclose(fout);
		printf("[*] File decrypted! Thanks :) \n");
		system("pause");
	}
	else {
		printf("[*] We can't find your specified file. Sorry! \n");
		system("pause");
	}



	return 0;
}
