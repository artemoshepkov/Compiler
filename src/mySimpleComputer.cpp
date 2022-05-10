#include "mySimpleComputer.h"

using namespace std;

int arrayMemory[SIZEARRAYMEMORY];
int flag;
int instructionCounter;
int accumulator;
int terminal = 0;

bool sc_verifyCommand(int number)
{
    if ((number >> 14) == 0)
        return true;
    return false;
}

int sc_memoryInit()
{
    for (int i = 0; i < SIZEARRAYMEMORY; i++)
    {
        arrayMemory[i] = i + 10 << 7;
    }
    instructionCounter = 0;
    accumulator = 0;
    sc_regInit();

    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address > SIZEARRAYMEMORY - 1)
    {
        sc_regSet(OUT_OF_MEMORY, 1);
        return -1;
    }
    if ((value & 0b1111111111111) > MAX_NUMBER_MEMORY)
    {
        sc_regSet(OVERFLOW, 1);
        return -1;
    }

    arrayMemory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if (address < 0 || address > SIZEARRAYMEMORY - 1)
    {
        sc_regSet(OUT_OF_MEMORY, 1);

        return -1;
    }
    
    *value = arrayMemory[address];

    return 0;
}

int sc_memorySave(char* filename)
{
    FILE *pFile = fopen(filename, "wb");

    for(int i = 0; i < 100; i++){
        fwrite(&arrayMemory[i], sizeof(int), 1, pFile);
    }

    fclose(pFile);

    return 0;
}

int sc_memoryLoad(char* filename)
{
    FILE* pFile = fopen(filename, "rb");
    
    for(int i = 0; i < 100; i++){
        fread(&arrayMemory[i], sizeof(int), 1, pFile);
    }
    
    fclose(pFile);

    return 0;
}

int sc_regInit(void)
{
    flag = 0;

    return 0;
}

int sc_regSet(int reg, int value)
{
    if (reg > 0 || reg < 6)
    {
        if (value == 0)
        {
            flag = flag & (~(1 << (reg - 1)));
        }
        else if (value == 1)
        {
            flag = flag | (1 << (reg - 1));
        }
        else
            return -1;
    }
    else
        return -1;

    return 0;
}

int sc_regGet(int reg)
{
    if (reg < 1 || reg > 5)
        return -1;
    return (flag >> (reg - 1)) & 0x1;
}

int sc_commandEncode(int command, int operand, int* value)
{
    if (command < 0 || command > 127 || operand < 0 || operand > 127)
    {
        sc_regSet(WRONG_COMMAND, 1);
        return -1;
    }

    (*value) = 0;
    (*value) = (command << 7) | operand;

    return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    if (value >> 14 != 0)
    {
        sc_regSet(WRONG_COMMAND, 1);
        return -1;
    }

    (*operand) = value & 0b00000001111111;
    (*command) = value >> 7;

    return 0;
}

void translationToAdditionalCode(int* number)
{
    if (((*number >> 13) & 0b1) == 1)
    {
        *number = ~(*number);
        *number &= 0b1111111111111;
        *number += 1;
        *number |= (0b1 << 13);
    }
}

void translationToStraightCode(int* number)
{
    if ((*number >> 13) == 0b11)
    {
        *number -= 1;
        *number = ~(*number);
        *number &= 0b1111111111111;
        *number |= (0b11 << 13);
    }
    else
    {
        *number |= (0b10 << 13);
    }
}