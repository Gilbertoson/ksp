cmake_minimum_required(VERSION 3.26)
project(KSP23 C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-g -Wall -pedantic main.c memory.c readProgram.c)

add_executable(KSP23 main.c
        memory.c
        global/opcodes.h
        memory.h
        global/versionNumber.h
        readProgram.h
        readProgram.c
        programInstructions.h
)
