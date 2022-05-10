#pragma once

#include <string>
#include <map>
#include "CU.h"

typedef void (*foo) ();

extern std::map <std::string, foo> commandsTerminal;

void initMapCommand();
void arrowUp();
void arrowDown();
void arrowLeft();
void arrowRight();
void step();
void reset();
void saveMemory();
void loadMemory();
void overWriteAccum();
void overWriteInstructCount();
void run();
void stopRunning(); 