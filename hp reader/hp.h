#ifndef HP
#define HP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VERSION_U	"Unknown"
#define VERSION_1	"HexPatch v1"
#define VERSION_2	"HexPatch v2"
#define VERSION_3	"HexPatch v3"

#define TRUE  1
#define FALSE 0

typedef unsigned char dbyte;

int isNum(int c) {
	if(0x30 <= c && 0x39 >= c)
		return TRUE;
	return FALSE;
}
// upper case char
int isUChar(int c) {
	if (0x41 <= c && 0x5A >= c)
		return TRUE;
	return FALSE;
}
// lower case char
int isLChar(int c) {
	if (0x61 <= c && 0x7a >= c)
		return TRUE;
	return FALSE;
}

char* getHPVersion(char* buff) {
	if ((buff = strstr(buff, "HexPatch"))) {
		if (strstr(buff, "v1")) 
			return VERSION_1;
		else if (strcmp(buff, "v2")) 
			return VERSION_2;
		else if (strcmp(buff, "v3")) 
			return VERSION_3;
		else 
			return VERSION_U;
	}
	return VERSION_U;
}

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

dbyte toHex(char c)
{
	if (isNum(c))
		return c - 0x30;
	else if (isLChar(c))
		return c - 0x57;
	else if (isUChar(c))
		return c - 0x37;
	else
		return -1;
}

// "1e ff 2f e1" to 0x1eff2fe1
dbyte* strh2hex(char* str, int* retLen) {
	int len = strlen(str);
	// Error handling
	if (len == 0) return -2;

	dbyte* ret = (dbyte*)malloc(sizeof(dbyte) * len / 3);
	// Error handling
	if (ret == NULL) {
		*retLen = 0;
		return -1;
	}

	int j = 0;
	for (int i = 0; i < len; i += 3) {
		int highPart = toHex(str[i]);
		int lowPart = toHex(str[i + 1]);
		if (highPart == -1 || lowPart == -1)
			continue;
		*(ret + j++) = (highPart << 4) + lowPart; // move high part from low part to high part
	}

	*retLen = j;
	return ret;
}

long strHOffset2Long(char *str)
{
	if(str != NULL)
	{
		long ret;
		int res = sscanf_s(str, "%lx", &ret);
		return (res != 1) ? -1 : ret;
	}
	return -2;
}

long fileSize(const char* filename) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) return 0;

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fclose(fp);

	return size;
}

#endif

/*
HexPatch v3

INCLUDE
{
	"I1" "libcocos2dcpp.so"
	"I2" "libmon.dll"
	"O1" "libcocos2dcppMod.so"
	"O2" "lobmonMod.dll"
	...
}

DEFINE
{
	"MOD1" "01 00 A0 E3"
	"MOD2" "01 10 A0 E3"
	...
}

CODE
{
    "0xaef"
	"01 00 A0 E1"
	"1E FF 2F E1"
}
CODE
{
	"0xaef"
	"01 00 A0 E1"
	"1E FF 2F E1"
}
CODE
{
	"0xaef"
	"01 00 A0 E1"
	"1E FF 2F E1"
}
*/

/*
HexPatch v2

%INC "libcocos2dcpp.so"
%OUT "libcocos2dcppMod.so"
%DEF a b
...

%START

.CODE
.OFFSET: 0xabc0
.ORIGINAL: 00 10 A0 E3
.REPLACED: 01 10 A0 E3

.CODE
.OFFSET: 0xabc0
.ORIGINAL: 00 10 A0 E3 
.REPLACED: 01

.CODE
.OFFSET: 0xabc0
.ORIGINAL: 00
.REPLACED: 01

%END
*/

/*
HexPatch v1

INCLUDE: libcocos2dcpp.so

CODE: Unlimited Health
OFFSET: 0x57d8b0
REPLACED: 1E FF 2F E1

CODE: Unlimited Flying Power
OFFSET: 0x57c770
REPLACED: 01 00 A0 E3 1E FF 2F E1

CODE: 1 Kill 10 Kill
OFFSET: 0x56940c
REPLACED: 0A

END
*/