#include "CommandInterface.h"
#include "mySimpleComputer.h"
#include "viewInterface.h"
#include "myReadKey.h"

std::map <std::string, foo> commandsTerminal;

void initMapCommand()
{
    commandsTerminal.emplace("\E[A", arrowUp);
    commandsTerminal.emplace("\E[B", arrowDown);
    commandsTerminal.emplace("\E[D", arrowLeft);
    commandsTerminal.emplace("\E[C", arrowRight);
    commandsTerminal.emplace("t", step);
    commandsTerminal.emplace("i", reset);
    commandsTerminal.emplace("s", saveMemory);
    commandsTerminal.emplace("l", loadMemory);
    commandsTerminal.emplace("r", run);
    commandsTerminal.emplace("\E[15~", overWriteAccum); // f5
    commandsTerminal.emplace("\E[17~", overWriteInstructCount); // f6
    commandsTerminal.emplace("a", stopRunning);
}

void arrowUp()
{
    if (instructionCounter > 9)
    {
        instructionCounter -= 10;
    }
}
void arrowDown()
{
    if (instructionCounter < 90)
    {
        instructionCounter += 10;
    }
}
void arrowLeft()
{
    if (instructionCounter > 0)
    {
        instructionCounter--;
    }
}
void arrowRight()
{
    if (instructionCounter < 99)
    {
        instructionCounter++;
    }
}
void step()
{
    if (instructionCounter < 99)
    {
        if (CU() == 0)
            instructionCounter++;
    }
    else
    {
        sc_regSet(IGNORE_TACTS, 1);
    }
}
void reset()
{
    for (int i = 0; i < SIZEARRAYMEMORY; i++)
    {
        arrayMemory[i] = 0;
    }
    instructionCounter = 0;
    accumulator = 0;
    flag = 0;
    terminal = 0;
    sc_regSet(IGNORE_TACTS, 1);
}
void saveMemory()
{
    char fileName[] = "memory.o";
    sc_memorySave(fileName);
}
void loadMemory()
{
    char fileName[] = "memory.o";
    sc_memoryLoad(fileName);
}
void overWriteAccum()
{
    int value = rk_readKey(0);
    if ((value & 0b1111111111111) > MAX_NUMBER_MEMORY)
    {
        sc_regSet(OVERFLOW, 1);
    }

    accumulator = value;
}
void overWriteInstructCount()
{
    int value = rk_readKey(0);
    if (value >= 0 && value < 100)
        instructionCounter = value;

}
void run()
{
    sc_regSet(IGNORE_TACTS, 0);
}
void stopRunning()
{
    sc_regSet(IGNORE_TACTS, 1);
}