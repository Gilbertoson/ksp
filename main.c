#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "readProgram.h"
//#include "global/debugger.h"
#include "global/versionNumber.h"
#include "memory.h"

#define NORMAL "\033[0;m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define RED "\033[0;31m"


void arguments(char* arg);
bool stringCompare(const char* str1, const char* str2);

int main(int argc, char *argv[]) {
    printf("Ninja Virtual Machine started\n");
    for (int i = 1; i < argc; ++i) {
        arguments(argv[i]);
    }

    printf("Ninja Virtual Machine stopped\n");
    return 0;
}

void arguments(char* arg){
    if (stringCompare(arg, "--help")) {
        printf("usage: ./njvm [option] [option] ...\n");
        printf("\t%s--version\t%sshow version and %sexit\n", BLUE, NORMAL, CYAN);
        printf("\t%s--help\t\t%sshow this %shelp %sand %sexit\n", BLUE, NORMAL, CYAN, NORMAL, CYAN);
        printf("\t%s--prog1\t\t%sexecute first program and %sexit\n", BLUE, NORMAL, CYAN);
        printf("\t%s--debug\t\t%sdebug the Programm\n", BLUE, NORMAL);
    } else if (stringCompare(arg, "--version")) {
        printf("Ninja Virtual Machine version %d (compiled %s, %s )\n", VERSION_NUMBER, __DATE__, __TIME__);
    }else if(*(&arg[0]) != '-' && *(&arg[1]) != '-') {
        readFile(arg);
        executionSeq();
    }
    else {
        printf("unkown %scommand %sline argument %s'%s'", CYAN, NORMAL, RED, arg);
        printf("%s, try %s'./njvm --help'\n", NORMAL, RED);
    }
}

bool stringCompare(const char* str1, const char* str2){
    int result = strcmp(str1, str2);
    return result  == 0 ? true : false;
}
