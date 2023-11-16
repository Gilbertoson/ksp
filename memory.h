//
// Created by gilbertson on 11/9/23.
//

#ifndef KSP23_MEMORY_H
#define KSP23_MEMORY_H

#define FALSE 0
#define TRUE 1

#define STACK_SIZE 10000

void executionSeq(void);


extern int debug;

extern int stack[STACK_SIZE];
extern int sp;
extern int fp;

extern int* sda;
extern int* program_memory;

extern int sda_size;
extern int numberOfInstr;
extern int pc;


#endif //KSP23_MEMORY_H
