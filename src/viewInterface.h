#pragma once

#include <iostream>
#include <iomanip>
#include "mySimpleComputer.h"
#include "myBigChars.h"
#include "myTerm.h"
#include "bigSymbols.h"
#include <string>
#include <algorithm>

extern int LEFT_TOP_ANGLE_INTERFACE;

int in_printInterface();
int in_printMemory(int leftTopAngle);
int in_printAccumulator(int leftTopAngleX, int leftTopAngleY);
int in_printOperation(int leftTopAngleX, int leftTopAngleY);
int in_printFlags(int leftTopAngleX, int leftTopAngleY);
int in_printInstructionCounter(int leftTopAngleX, int leftTopAngleY);
int in_printKeys(int leftTopAngleX, int leftTopAngleY);
int in_printBigChars(int index, int leftTopAngleX, int leftTopAngleY);
int in_terminal(int leftTopAngleX, int leftTopAngleY);