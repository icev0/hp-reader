#ifndef _MIN_HEX_EDITOR
#define _MIN_HEX_EDITOR
// Minimal HexEditor by THE ICE

#ifndef _INC_STDIO
#include <stdio.h>
#endif

int replace(char* filename, long offset, unsigned char* replaced, size_t length) {
    FILE* fptr = fopen(filename, "rb+"); // read & write binary, if not exist return an error
    if (fptr != NULL) {
        fseek(fptr, offset, SEEK_SET);
        fwrite(replaced, sizeof(*replaced), length, fptr);
        fclose(fptr);
        return 0;
    }
    return -1;
}

int isReplaced(char* filename, long offset, unsigned char* replaced, size_t length) {
    FILE* fptr = fopen(filename, "rb");
    if (fptr != NULL) {
        fseek(fptr, offset, SEEK_SET);
        unsigned char* check = (unsigned char*)malloc(length * sizeof(*check));
        if (check == NULL) {
            fclose(fptr);
            return -3; // Memory allocation failed
        }
        fread(check, sizeof(*check), length, fptr);
        fclose(fptr);

        int res = memcmp(check, replaced, length);
        free(check);

        return (res == 0) ? 0 : -1; // if Replacement was successful return 0 else return error
    }
    return -2; // File could not be opened
}

#endif // _MIN_HEX_EDITOR