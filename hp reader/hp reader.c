#include "hp.h"
#include "hpv1.h"
#include "editor.h"

int err = 0;

void exitProg(int);

int main(int argc, char** argv) {
	char* hpfile;
	dbyte isMemAllocated = 0;
	
	if (argc < 2) {
		hpfile = (char*)malloc(HP_FILENAME_SIZE);
		if (hpfile == NULL)
		{
			puts("[!] Error: RAM is full!\n[?] Help: Free your RAM memory by closing some app");
			exitProg(EXIT_FAILURE);
		}
		
		puts("[+] Enter hp file path: ");
		scanf("%254s", hpfile);

		*(hpfile + HP_FILENAME_SIZE - 1) = NULL;
#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif
		isMemAllocated = TRUE; // controll last free memory
	}
	else
		hpfile = argv[1];

	FILE* fp;
	char* buff = (char*)malloc(fileSize(hpfile));
	// ERROR HANDLING
	if (buff == NULL) {
		puts("[!] Error: RAM is full!\n[?] Help: Free your RAM memory by closing some app");
		exitProg(EXIT_FAILURE);
	}

	fp = fopen(hpfile, "r");
	// ERROR HANDLING
	if (fp == NULL) {
		puts("[!] Error: Cannot open the hp script file!\n[?] Help: Check your script file name or Check it's open in another app!");
		exitProg(EXIT_FAILURE);
	}
	
	char c;
	int i = 0;
	while ((c = getc(fp)) != EOF)
		*(buff + i++) = c;
	// end of string
	*(buff + i) = NULL;
	
	// close file
	fclose(fp);

	// code
	err = isHexPatchFile(hpfile, buff);
	// get included file name inside of the hp file
	const char* getIncFnm = getIncludedFile(buff);
	if (getIncFnm == MEM_ALLOC_ERR) {
		puts("[!] Error: RAM is full!\n[?] Help: Free your RAM memory by closing some app");
		exitProg(EXIT_FAILURE);
	}
	// else
	if (err != SUCCESS)
	{
		if (err == INCLUDE_NOT_FOUND) {
			puts("[!] Syntax error: 'INCLUDE' tag not found!\n[?] Help: Check the document");
			exitProg(EXIT_FAILURE);
		}

		if (err == VERSION_NOT_FOUND) {
			puts("[!] Syntax error: HexPatch Version not found!\n[?] Help: Check the document");
			exitProg(EXIT_FAILURE);
		}

		if (err == FILE_NOT_FOUND) {
			printf("[!] Syntax error: %s included file not found!\n[?] Help: Check your target file name or Check it's open in another app\n", getIncFnm);
			exitProg(EXIT_FAILURE);
		}

		if (err == ERR_WITH_CODES) {
			puts("[!] Syntax error: error with number of codes/offsets/replaceds (They're not match)\n[?] Help: Check the document");
			exitProg(EXIT_FAILURE);
		}
	}
	// errors successed
	puts("[*] HP Reader - HexPatch Script interpreter\n");

	printf("[+] Loading Script: %s\n", hpfile);
	printf("[+] Version: %s\n", getHPVersion(buff));
	printf("[+] Loading File: %s\n\n", getIncFnm);
	
	char* currCode;
	char* currOffset;
	char* currReplaced;

	long   OFFSET;
	dbyte* REPLACED;
	int    rLen    = 0;
	int	   succRun = 0;
	int	   failRun = 0;

	const int numberOfCodes = getNumberOfCodes(hpfile);

	for (register int i = 0; i < numberOfCodes; i++) {
		// Get code from file
		currCode = getCode(hpfile, buff, i);
		// Error handling
		if (currCode == NULL)
			puts("[??] Syntax warning: Code name is NULL are you sure about that!");
		// then
		printf("[+] GET Code: %s\n", currCode);

		// Get offset from file
		currOffset = getOffset(hpfile, buff, i);
		// Error handling
		if (currOffset == NULL)
		{
			puts("[!] Syntax error: Offset is NULL\n[!] Interpreter will jump this code!\n");
			failRun++;
			continue;
		}
		// else
		printf("[+] GET Offset: %s\n", currOffset);
		
		// Get replaced from file
		currReplaced = getReplaced(hpfile, buff, i);
		// Error handling
		if (currReplaced == NULL)
		{
			puts("[!] Syntax error: Replaced is NULL, Are you sure about that!\n[!] Interpreter will jump this code!\n");
			failRun++;
			continue;
		}
		// else
		printf("[+] GET Replaced: %s\n\n", currReplaced);
		
		// Modify process
		puts("[*] Modifying...");

		OFFSET = strHOffset2Long(currOffset);
		REPLACED = strh2hex(currReplaced, &rLen);

		// ERROR HANDLING (OFFSET == -1 || OFFSET == -2)
		if (OFFSET < SUCCESS) {
			printf("[!] Syntax error: Failed to convert Offset\n[?] Help: check your OFFSET of %s Code\n", currCode);
			exitProg(EXIT_FAILURE);
		}
		// ERROR HANDLING
		if (REPLACED < SUCCESS) {
			printf("[!] Syntax error: Failed to convert Replaced\n[?] Help: Check your REPLACED of %s Code\n", currCode);
			exitProg(EXIT_FAILURE);
		}
		// Set the end
		*(REPLACED + rLen) = NULL;

		// EDITING TARGET FILE
		err = replace(getIncFnm, OFFSET, REPLACED, rLen);
		// ERROR HANDLING
		if (err != SUCCESS) {
			puts("[!] Error: error with editing INCLUDED file");
			exitProg(EXIT_FAILURE);
		}
		// Check edited bytes
		err = isReplaced(getIncFnm, OFFSET, REPLACED, rLen);
		if (err == SUCCESS)
		{
			succRun++;
			puts("[*] Modified Successfull.\n");
		}
		else
		{
			failRun++;
			puts("[*] Error: error with editing bytes!\n");
		}
		// Freeing MEMORY
		free(currCode);
		free(currReplaced);
		free(currOffset);
	}

	putchar(NEW_LINE);
	
	if(succRun == numberOfCodes)
		puts("[*] The script was completed successfully.");
	else
		printf("[*] The script was completed with\n[+] %d code(s) successfuly\n[!] %d code(s) failure\n", succRun, failRun);
	// freeing allocated memory
	if (isMemAllocated) free(hpfile);
	free(buff);
	free(getIncFnm);
	// finished
	exitProg(EXIT_SUCCESS);
}

void exitProg(int ret)
{
#ifdef _WIN32
	system("pause");
#else
	system("echo \"Press enter to continue!\" && read");
#endif
	exit(ret);
}