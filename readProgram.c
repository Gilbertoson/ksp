//
// Created by gilbertson on 11/9/23.
//

//#include <bits/types/FILE.h>
#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>

#include "readProgram.h"
#include "programInstructions.h"
#include "global/versionNumber.h"

int getNextFourBytes(FILE* fp) {
    int result[1];
    fread(result, 4, 1, fp);
    return result[0];
}

void validateFile(FILE* fp) {
    //ValidateFormat
    char format[4];
    fread(format, 1, 4, fp);
    if(format[0] != 'N' && format[1] != 'J' && format[2] != 'B' && format[3] != 'F') {
        exit(3);
    }
    //ValidateVersionNumber
    if(getNextFourBytes(fp) != VERSION_NUMBER) {
        exit(10);
    }
}

void readFile(const char* filePath) {
    FILE* fp = NULL;
    if((fp = fopen(filePath, "r")) == NULL) {
        exit(5);
    }
    validateFile(fp);

    numberOfInstr = getNextFourBytes(fp);
    sda_size = getNextFourBytes(fp);

    program_memory = malloc(numberOfInstr * sizeof(unsigned int));
    sda = malloc(sda_size * sizeof(unsigned int));

    for(int i = 0; i < numberOfInstr; i++) {
        program_memory[i] = getNextFourBytes(fp);
    }

    fclose(fp);
}
