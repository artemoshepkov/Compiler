#pragma once

#include <iostream>
#include <string>

#define OVERFLOW 1 // переполнение при выполнении операции 
#define DIVISION_ZERO 2 // деление на 0 
#define OUT_OF_MEMORY 3 // ошибка выхода за границы памяти 
#define IGNORE_TACTS 4 // игнорирование тактовых импульсов
#define WRONG_COMMAND 5 // указана неверная команда

#define SIZEARRAYMEMORY 100
#define MAX_NUMBER_MEMORY 8191

extern int arrayMemory[SIZEARRAYMEMORY];
extern int flag;
extern int instructionCounter;
extern int accumulator;
extern int terminal;

bool sc_verifyCommand(int number);
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
int sc_accumulatorSet(int value);


void translationToAdditionalCode(int *number);
void translationToStraightCode(int *number);

