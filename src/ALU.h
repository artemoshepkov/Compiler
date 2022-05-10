#pragma once

#include <iostream>
#include <map>

#include "mySimpleComputer.h"

typedef int (*foo1) (int value);

extern std::map <int, foo1> ALUCommands;

int ALU(int command, int operand);

void initMapALUCommand();

int ALU_add(int value);
int ALU_sub(int value);
int ALU_divide(int value);
int ALU_mul(int value);