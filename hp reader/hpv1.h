#ifndef HPV1
#if defined(HPV2) || defined(HPV3)
#error "Error with HP version included files"
#endif

#define HPV1

#ifndef HP
#include "hp.h"
#endif

#define VERSION				"HexPatch v1"

#define HP_FILENAME_SIZE	255

#define NEW_LINE 			'\n'
#define SPECIAL_KEY			'0'
// Errors
#define MEM_ALLOC_ERR		-4
#define FILE_NOT_FOUND 		-3
#define INCLUDE_NOT_FOUND 	-2
#define VERSION_NOT_FOUND 	-1
#define SUCCESS 			 0
#define ERR_WITH_CODES 		 1
// Syntax
#define INC_DEF				"INCLUDE: "
#define CODE_DEF			"CODE: "
#define OFFSET_DEF			"OFFSET: "
#define REPLACED_DEF		"REPLACED: "
#define INC_DEF_LEN			9
#define CODE_DEF_LEN		6
#define OFFSET_DEF_LEN		8
#define REPLACED_DEF_LEN	10

char* getIncludedFile(char *buff) {
	int address, pos;
	char* result = strstr(buff, INC_DEF);
	pos = result - buff;
	int substrLength = strlen(buff) - pos;
	char *nwBuffer = (char *)malloc(substrLength);
	address = pos + INC_DEF_LEN;

	int i = 0, c = address;
	while (i < substrLength+1)
	{
		if (*(buff + c++) == NEW_LINE) {
			*(nwBuffer + i) = NULL;
			return nwBuffer;
		}
		*(nwBuffer + i++) = *(buff + c - 1);
	}
	return nwBuffer;
}

int isHexPatchFile(char* fn, char* buff) {
	if (!strstr(buff, INC_DEF)) return INCLUDE_NOT_FOUND;
	// else
	char* fname = getIncludedFile(buff);
	if (fopen(fname, "r") == NULL) {
		free(fname);
		return FILE_NOT_FOUND;
	}
	if (strcmp(VERSION_U, getHPVersion(buff)) == 0) return VERSION_NOT_FOUND;
	// if there is any code
	if (strstr(buff, CODE_DEF))
		if (getNumberOfCodes(fn) != getNumberOfOffsets(fn) || getNumberOfCodes(fn) != getNumberOfReplaceds(fn))
			return ERR_WITH_CODES;
	return SUCCESS;
}

char* getCode(char *filename, int index) {
	int nCode = getNumberOfCodes(filename);

	if (index > nCode) return "[!] Syntax error: Error with index";

	FILE* fp = fopen(filename, "r");
	char *buffer = (char*)malloc(fileSize(filename));
	if (buffer == NULL) return MEM_ALLOC_ERR;
	int c, i = 0;

	while ((c = getc(fp)) != EOF)
		*(buffer + i) = c, i++;
	*(buffer +i) = NULL;
	fclose(fp);

	char* result;
	int searchLen = CODE_DEF_LEN;

	for (int n = 0; n < nCode; n++) {
		result = strstr(buffer, CODE_DEF);
		if (!result) return NULL;

		int pos = result - buffer;
		int subLen = strlen(buffer) - pos;
		int address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char *)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			for (int c = address, j = 0; j < subLen; j++, c++) {
				if (*(buffer + c) == NEW_LINE) {
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j) = *(buffer + c);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++) 
				*(result + j) = SPECIAL_KEY;
			strcpy(buffer, result);
		}
	}
	return NULL;
}

char* getOffset(char* filename, int index) {
	int nOffset = getNumberOfOffsets(filename);

	if (index > nOffset) return "[!] Syntax error: Error with index";

	FILE* fp = fopen(filename, "r");
	char *buffer = (char *)malloc(fileSize(filename));
	if (buffer == NULL) return MEM_ALLOC_ERR;
	int c, i = 0;

	while ((c = getc(fp)) != EOF)
		*(buffer + i) = c, i++;
	*(buffer + i) = NULL;
	fclose(fp);

	char* result;
	int searchLen = OFFSET_DEF_LEN;

	for (int n = 0; n < nOffset; n++) {
		result = strstr(buffer, OFFSET_DEF);
		if (!result) return NULL;

		int pos = result - buffer;
		int subLen = strlen(buffer) - pos;
		int address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char *)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			for (int c = address, j = 0; j < subLen; j++, c++) {
				if (buffer[c] == NEW_LINE) {
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j) = *(buffer + c);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++) *(result + j) = SPECIAL_KEY;
			strcpy(buffer, result);
		}
	}
	return NULL;
}

char* getReplaced(char* filename, int index) {
	int nReplaced = getNumberOfReplaceds(filename);

	if (index > nReplaced) return "[!] Syntax error: Error with index";

	FILE* fp = fopen(filename, "r");
	char* buffer = (char*)malloc(fileSize(filename));
	if (buffer == NULL) return MEM_ALLOC_ERR;
	int c, i = 0;

	while ((c = getc(fp)) != EOF)
		*(buffer + i) = c, i++;
	*(buffer + i) = NULL;
	fclose(fp);

	char* result;
	int searchLen = REPLACED_DEF_LEN;

	for (int n = 0; n < nReplaced; n++) {
		result = strstr(buffer, REPLACED_DEF);
		if (!result) return 0;

		int pos = result - buffer;
		int subLen = strlen(buffer) - pos;
		int address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char *)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			for (int c = address, j = 0; j < subLen; j++, c++) {
				if (buffer[c] == NEW_LINE) {
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j) = *(buffer + c);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++) *(result + j) = SPECIAL_KEY;
			strcpy(buffer, result);
		}
	}
	return NULL;
}

#endif // !HPV1