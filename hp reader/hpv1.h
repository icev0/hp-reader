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
#define SPECIAL_CHR			'0'
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

int getNumberOfCodes(char* fname) {
	FILE* fp;
	char str[20];
	int counter = 0;

	fp = fopen(fname, "r");
	if (fp == NULL) return -1;

	while (fscanf(fp, "%19s", str) == 1)
		if (strcmp(str, "CODE:") == 0)
			counter++;

	fclose(fp);
	return counter;
}

int getNumberOfOffsets(char* fname) {
	FILE* fp;
	char str[20];
	int counter = 0;

	fp = fopen(fname, "r");
	if (fp == NULL) return -1;

	while (fscanf(fp, "%19s", str) == 1)
		if (strcmp(str, "OFFSET:") == 0)
			counter++;

	fclose(fp);
	return counter;
}

int getNumberOfReplaceds(char* fname) {
	FILE* fp;
	char str[20];
	int counter = 0;

	fp = fopen(fname, "r");
	if (fp == NULL) return -1;

	while (fscanf(fp, "%19s", str) == 1)
		if (strcmp(str, "REPLACED:") == 0)
			counter++;

	fclose(fp);
	return counter;
}

char* getIncludedFile(char* buff) {
	char* result = strstr(buff, INC_DEF);
	// ERROR HANDLING
	if (!result) return NULL;
	int pos = result - buff,
		substrLength = strlen(buff) - pos,
		address = pos + INC_DEF_LEN;

	char* nwBuffer = (char*)malloc(substrLength);
	if (nwBuffer == NULL) return MEM_ALLOC_ERR;

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
	if (strcmp(VERSION_1, getHPVersion(buff)) != 0) return VERSION_NOT_FOUND;
	// if there is any code
	if (strstr(buff, CODE_DEF))
		if (getNumberOfCodes(fn) != getNumberOfOffsets(fn) || getNumberOfCodes(fn) != getNumberOfReplaceds(fn))
			return ERR_WITH_CODES;
	return SUCCESS;
}

char* getCode(char* filename, char *buff, int index) {
	int nCode = getNumberOfCodes(filename);

	if (index > nCode) return "[!] Syntax error: Error with index";

	char* buffer = (char*)malloc(strlen(buff)+1);
	if (buffer == NULL) return MEM_ALLOC_ERR;
	strcpy(buffer, buff);
	
	char* result;
	int searchLen = CODE_DEF_LEN;

	for (int n = 0; n < nCode; n++) {
		result = strstr(buffer, CODE_DEF);
		if (!result) return NULL;

		int pos = result - buffer,
			subLen = strlen(buffer) - pos,
			address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char*)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			int c = address, j = 0;
			while (j < subLen)
			{
				if (*(buffer + c++) == NEW_LINE) {
					free(buffer);
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j++) = *(buffer + c - 1);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++) 
				*(result + j) = SPECIAL_CHR;
			strcpy(buffer, result);
		}
	}
	free(buffer);
	return NULL;
}

char* getOffset(char* filename, char* buff, int index) {
	int nOffset = getNumberOfOffsets(filename);

	if (index > nOffset) return "[!] Syntax error: Error with index";

	char* buffer = (char*)malloc(strlen(buff) + 1);
	if (buffer == NULL) return MEM_ALLOC_ERR;
	strcpy(buffer, buff);

	char* result;
	int searchLen = OFFSET_DEF_LEN;

	for (int n = 0; n < nOffset; n++) {
		result = strstr(buffer, OFFSET_DEF);
		if (!result) return NULL;

		int pos = result - buffer,
			subLen = strlen(buffer) - pos,
			address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char*)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			int c = address, j = 0;
			while (j < subLen)
			{
				if (*(buffer + c++) == NEW_LINE) {
					free(buffer);
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j++) = *(buffer + c - 1);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++)
				*(result + j) = SPECIAL_CHR;
			strcpy(buffer, result);
		}
	}
	free(buffer);
	return NULL;
}

char* getReplaced(char* filename, char* buff, int index) {
	int nReplaced = getNumberOfReplaceds(filename);

	if (index > nReplaced) return "[!] Syntax error: Error with index";

	char* buffer = (char*)malloc(strlen(buff) + 1);
	if (buffer == NULL) return MEM_ALLOC_ERR;
	strcpy(buffer, buff);

	char* result;
	int searchLen = REPLACED_DEF_LEN;

	for (int n = 0; n < nReplaced; n++) {
		result = strstr(buffer, REPLACED_DEF);
		if (!result) return NULL;

		int pos = result - buffer,
			subLen = strlen(buffer) - pos,
			address = pos + searchLen;

		if (n == index) {
			char* retBuffer = (char*)malloc(subLen);
			if (retBuffer == NULL) return MEM_ALLOC_ERR;

			int c = address, j = 0;
			while (j < subLen)
			{
				if (*(buffer + c++) == NEW_LINE) {
					free(buffer);
					*(retBuffer + j) = NULL;
					return retBuffer;
				}
				*(retBuffer + j++) = *(buffer + c - 1);
			}
		}
		else {
			for (int j = 0; j < searchLen; j++)
				*(result + j) = SPECIAL_CHR;
			strcpy(buffer, result);
		}
	}
	free(buffer);
	return NULL;
}

#endif // !HPV1