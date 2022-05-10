#include "CU.h"

std::map <int, foo2> CUCommands;

int CU()
{
    if ((arrayMemory[instructionCounter] >> 14) == 1)
    {
        return 0;
    }
    int command, operand;
    if (sc_commandDecode(arrayMemory[instructionCounter], &command, &operand) == 0)
    {
        if (command > 47 && command < 52)
        {
            if (ALU(command, operand) == -1)
            {
                return -1;
            }
        }
        else
        {
            if (CUCommands.find(command) != CUCommands.end())
            {
                if (CUCommands[command](operand) == -1)
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        sc_regSet(WRONG_COMMAND, 1);
        return -1;
    }

    return 0;
}

int CU_read(int address)
{
    int value = 0;
    std::cout << "ype: ";
    std::cin >> value;

    if (value < 0)
    {
        value &= 0b1111111111111;
        value |= (0b1 << 13);
    }
    value |= (0b1 << 14);


    if (sc_memorySet(address, value) == 0)
        return 0;

    return -1;
}
int CU_write(int address)
{
    if (sc_memoryGet(address, &terminal) == 0)
    {
        return 0;
    }

    return -1;
}
int CU_load(int address)
{
    if (sc_memoryGet(address, &accumulator) == 0)
        return 0;
    return -1;
}
int CU_store(int address)
{
    if (sc_memorySet(address, accumulator) == 0)
        return 0;
    return -1;

}
int CU_jump(int address)
{
    if (address < 0 || address > SIZEARRAYMEMORY)
    {
        sc_regSet(OUT_OF_MEMORY, 1);
        return -1;
    }
    instructionCounter = address - 1;
    return 0;
}
int CU_jneg(int address)
{
    if (((accumulator >> 13) & 0b1) == 1)
    {
        CU_jump(address);
    }

    return 0;
}
int CU_jz(int address)
{
    if ((accumulator & 0b1111111111111) == 0)
    {
        CU_jump(address);
    }

    return 0;
}
int CU_halt(int address)
{
    sc_regSet(IGNORE_TACTS, 1);

    return 0;
}

void initMapCUCommand()
{
    CUCommands.emplace(16, foo2(CU_read));
    CUCommands.emplace(17, foo2(CU_write));
    CUCommands.emplace(32, foo2(CU_load));
    CUCommands.emplace(33, foo2(CU_store));
    CUCommands.emplace(64, foo2(CU_jump));
    CUCommands.emplace(65, foo2(CU_jneg));
    CUCommands.emplace(66, foo2(CU_jz));
    CUCommands.emplace(67, foo2(CU_halt));

}