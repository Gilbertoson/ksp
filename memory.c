//
// Created by gilbertson on 11/9/23.
//
#include <stdio.h>
#include <stdlib.h>


#include "global/opcodes.h"
#include "memory.h"
//#include "readProgram.h"


void push(int item), add(void), sub(void), mul(void),divide(void), mod(void), rdchr(void), wrchr(void), rdint(
        void), wrint(void), execute(unsigned int ir), asf(int range), rsf(void), pushg(int offset),
        popg(int offset),pushl(int offset), popl(int offset), jump(int target), branch_on_false(int target),
        branch_on_true(int target),call(int target),ret(void),drop(int amountToDrop),pushr(void),popr(void),dup(void);

int equals(void), not_equals(void), lesser_than(void), lesser_equals(void), greater_than(void), greater_equals(void),pop(void);

//int debug = FALSE;
// chmod +x ./nja

int rvr = 0;
int sp=0;
int fp=0;
int pc=0;

int stack[STACK_SIZE];

int* sda;
int* program_memory;

int sda_size;
int numberOfInstr;


void executionSeq(void){
    while(pc < numberOfInstr){
        unsigned int ir =program_memory[pc++];
        execute(ir);
    }
}

void execute(unsigned int ir) {
    unsigned int op = ir >> 24;
    int immediate = SIGN_EXTEND(ir & 0x00FFFFFF);
    switch (op) {
        case HALT : {
            pc = numberOfInstr;
            break;
        }
        case PUSHC : {
            push(immediate);
            break;
        }
        case ADD : {
            add();
            break;
        }
        case SUB : {
            sub();
            break;
        }
        case MUL : {
            mul();
            break;
        }
        case DIV : {
            divide();
            break;
        }
        case MOD : {
            mod();
            break;
        }
        case RDINT : {
            rdint();
            break;
        }
        case WRINT : {
            wrint();
            break;
        }
        case RDCHR : {
            rdchr();
            break;
        }
        case WRCHR : {
            wrchr();
            break;
        }
        case PUSHG : {
            pushg(immediate);
            break;
        }
        case POPG : {
            popg(immediate);
            break;
        }
        case ASF :{
            asf(immediate);
            break;
        }
        case RSF : {
            rsf();
            break;
        }
        case PUSHL : {
            pushl(immediate);
            break;
        }
        case POPL : {
            popl(immediate);
            break;
        }
        case EQ : {
            push(equals());
            break;
        }
        case NE : {
            push(not_equals());
            break;
        }
        case LT : {
            push(lesser_than());
            break;
        }case LE : {
            push(lesser_equals());
            break;
        }
        case GT : {
            push(greater_than());
            break;
        }
        case GE : {
            push(greater_equals());
            break;
        }
        case JMP : {
            jump(immediate);
            break;
        }
        case BRF : {
            branch_on_false(immediate);
            break;
        }
        case BRT : {
            branch_on_true(immediate);
            break;
        }
        case CALL : {
            call(immediate);
            break;
        }
        case RET : {
            ret();
            break;
        }
        case DROP : {
            drop(immediate);
            break;
        }
        case PUSHR : {
            pushr();
            break;
        }
        case POPR : {
            popr();
            break;
        }
        case DUP : {
            dup();
            break;
        }
        /*case NEW : {
            new(immediate);
            break;
        }
        case GETF : {
            getf(immediate);
            break;
        }
        case PUTF : {
            putf(immediate);
            break;
        }
        case NEWA : {
            newa();
            break;
        }
        case GETFA : {
            getfa();
            break;
        }
        case PUTFA : {
            putfa();
            break;
        }
        case GETSZ : {
            getsz();
            break;
        }
        case PUSHN : {
            pushn();
            break;
        }
        case REFEQ : {
            refeq();
            break;
        }
        case REFNE : {
            refne();
            break;
        }*/
        default: {
            //printf("Error : no viable Instruction found\n Exit Program");
            exit(1);
        }
    }

}

void push(int item) {
    if (sp < 0) {
        //printf("Error: Stack overflow\n");
        exit(1);
    }
    stack[sp++] = item;
}

int pop(void) {
    if (sp <= 0) {
        //printf("Error: Stack underflow\n");
        exit(1);
    }
    int item = stack[--sp];
    return item;
}

void add(void) {
    int n1 = pop();
    int n2 = pop();
    push(n1 + n2);
    //printf("ADD: FP:  %d SP: %d\n",fp,sp);
    //printf("ADD: n1: %d n2:%d sum: %d\n",n1, n2,n1+n2);
}

void sub(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 - n1);
    //printf("SUB\n");
}

void mul(void) {
    int n1 = pop();
    int n2 = pop();
    push(n1 * n2);
    //printf("MUL: FP:  %d SP: %d\n",fp,sp);
    //printf("MUL: n1: %d n2: %d prod: %d \n",n1,n2,n1*n2);
}

void divide(void) {
    int n1 = pop();
    int n2 = pop();
    if(n1 == 0){
        //printf("Error: Cant divide by zero");
        exit(1);
    }else{
        push(n2 / n1);
    }
    //printf("DIV\n");
}

void mod(void) {
    int n1 = pop();
    int n2 = pop();
    if(n1 == 0){
        //printf("Error: Cant divide by zero");
        exit(1);
    }else{
        push(n2 % n1);
    }
    //printf("MOD\n");
}

void rdchr(void) {
    //printf("Enter value: ");
    char buffer[2]; //TODO check if size needs to be two
    fgets(buffer, sizeof(buffer),stdin);
    push((int) buffer[0]);
}

void wrchr(void) {
    printf("%c", pop());
    //printf("WRCHR\n");
}

void rdint(void) {
    //printf("Enter value: ");
    char buffer[24]; //32 bits - 8 bits = 24
    fgets(buffer, sizeof(buffer),stdin);
    push((int) strtol(buffer, NULL, 10));
}

void wrint(void) {
    printf("%d", pop());
    //printf("\nWRINT");
}

void pushg(int offset) {
    //printf("pushG\n");
    push((sda[offset]));
}

void popg(int offset) {
    //printf("popG\n");
    sda[offset] = pop();
}
void asf(int range){
    push(fp);
    fp = sp;
    sp = sp + range;
}
void rsf(void){
    sp = fp;
    fp = pop();
}

void pushl(int offset){
    //printf("Pre-PUSHL: FP:  %d Offset: %d SP: %d\n",fp,offset,sp);
    push(stack[fp + offset]);
    //printf("Post-PUSHL: FP:  %d Offset: %d SP: %d\n",fp,offset,sp);
}

void popl(int offset){
    //printf("Pre-POPL: FP:  %d Offset: %d SP: %d\n",fp,offset,sp);
    stack[fp+offset] = pop();
    //printf("Post-POPL: FP:  %d Offset: %d SP: %d\n",fp,offset,sp);
}

int equals(void){
    int n2 = pop();
    int n1 = pop();
    if(n1==n2){
        return TRUE;
    }
    return FALSE;
}

int not_equals(void){
    int n2 = pop();
    int n1 = pop();
    //printf("NE\n");
    if(n1!=n2){
        return TRUE;
    }
    return FALSE;

}
int lesser_than(void){
    int n2 = pop();
    int n1 = pop();
    if(n1 < n2){
        return TRUE;
    }
    return FALSE;
}
int lesser_equals(void){
    int n2 = pop();
    int n1 = pop();
    if(n1 <= n2){
        return TRUE;
    }
    return FALSE;
}
int greater_than(void){
    int n2 = pop();
    int n1 = pop();
    //printf("GT\n");
    if(n1 > n2){
        return TRUE;
    }
    return FALSE;
}

int greater_equals(void){
    int n2 = pop();
    int n1 = pop();
    if(n1 >= n2){
        return TRUE;
    }
    return FALSE;
}

void jump(int target){
    pc = target;
    //printf("Jmp\n");
}

void branch_on_false(int target){
    if(pop()== FALSE){
        pc = target;
    }
    // soll hier ein exit hin, wenn pop != 1 || 0?
}

void branch_on_true(int target){
    if(pop() == TRUE){
        pc = target;
    }
}
void call(int target) {
    push(pc);
    jump(target);
}

void ret(void) {
    jump(pop());
}

void drop(int amountToDrop) {
    while (amountToDrop-- > 0) {
        pop();
    }
}

void pushr(void) {
    push(rvr);
}

void popr(void) {
    rvr = pop();
}

void dup(void) {
    int item = pop();
    push(item);
    push(item);
}
/*
void new(int range){
    ObjRef cmpObj = initWithNullCmpObj(range);
    pushObject(cmpObj);
}

void getf(int position){
    ObjRef cmpObj = popObject();
    if(cmpObj->isCmpObj) {
        ObjRef objRef = ((ObjRef *) cmpObj->data)[position];
        pushObject(objRef);
    } else {
        //TODO ERROR Printen
    }
}
void putf(int position){
    ObjRef objRef = popObject();
    ObjRef cmpObj = popObject();
    if(cmpObj->isCmpObj) {
        ((ObjRef *) cmpObj->data)[position] = objRef;
    } else {
        //TODO ERROR Printen
    }
}

void newa(void){
    ObjRef numOfElements = popObject();
    bip.op1 = numOfElements;
    int size = bigToInt();
    //printf("Size: %d\n",size);
    ObjRef newCmpObj = initWithNullCmpObj(size);
    pushObject(newCmpObj);
    resetBip();
}

void getfa(void){
    ObjRef arrayPosition = popObject();
    bip.op1 = arrayPosition;
    int position = bigToInt();
    ObjRef cmpObj = popObject();
    if(cmpObj->isCmpObj){
        if(position >= 0 && position < (int)cmpObj->size){
            ObjRef objRef = ((ObjRef *) cmpObj->data)[position];
            pushObject(objRef);
        }else{
            printf("index out of bounds");
            exit(10);
        }
    } else {
        //TODO ERROR Printen
        printf("Error, GETFA");
        exit(1);
    }
    resetBip();
}
void putfa(void){
    ObjRef objRef = popObject();
    ObjRef arrayPosition = popObject();
    bip.op1 = arrayPosition;
    int position = bigToInt();
    ObjRef cmpObj = popObject();
    if(cmpObj->isCmpObj) {
        if(position >= 0 && position < (int)cmpObj->size){
            ((ObjRef *) cmpObj->data)[position] = objRef;
        }else{
            printf("index out of bounds");
            exit(10);
        }

    } else {
        //TODO ERROR Printen
        printf("ERROR, PUTFA");
        exit(1);
    }
    resetBip();
}
void getsz(void){
    ObjRef objRef = popObject();
    if(objRef->isCmpObj) {
        int size = (int) objRef->size;
        bigFromInt(size);
        pushObject(bip.res);
    } else  {
        bigFromInt(-1);
        pushObject(bip.res );
    }
    resetBip();
}
void pushn(void){
    pushObject(NULL);
}
void refeq(void){
    ObjRef ref2 = popObject();
    ObjRef ref1 = popObject();
    if(ref1 != ref2){
        bigFromInt(FALSE);
    } else {
        bigFromInt(TRUE);
    }
    pushObject(bip.res);
    resetBip();
}
void refne(void){
    ObjRef ref2 = popObject();
    ObjRef ref1 = popObject();
    if(ref1 == ref2){
        bigFromInt(FALSE);
    } else {
        bigFromInt(TRUE);
    }
    pushObject(bip.res);
    resetBip();
}

ObjRef initWithNullCmpObj(int amount_refs) {
    ObjRef objRef = newCmpObj(amount_refs);
    *(ObjRef *) objRef->data = NULL;
    objRef->isCmpObj = TRUE;
    objRef->size = amount_refs;
    for(int i = 0; i < amount_refs; i++) {
        ((ObjRef *) objRef->data)[i] = NULL;
    }

    return objRef;
}


// Necessary for the Bigint library
void* getPrimObjectDataPointer(void * obj){
    ObjRef oo = ((ObjRef) (obj));
    return oo->data;
}

void fatalError(char* msg){
    printf("%s\n", msg);
    exit(1);
}

void resetBip() {
    bip.op1 = NULL;
    bip.op2 = NULL;
    bip.res = NULL;
    bip.rem = NULL;
}*/
