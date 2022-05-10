#pragma once

#include <iostream>

#include "mySimpleComputer.h"
#include "ALU.h"

typedef int (*foo2) (int address);

extern std::map <int, foo2> CUCommands;

int CU();

void initMapCUCommand();
int CU_read(int address);
int CU_write(int address);
int CU_load(int address);
int CU_store(int address);
int CU_jump(int address);
int CU_jneg(int address);
int CU_jz(int address);
int CU_halt(int address);
