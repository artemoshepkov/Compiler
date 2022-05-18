#include "ALU.h" 

std::map <int, foo1> ALUCommands;

void initMapALUCommand()
{
    ALUCommands.emplace(48, foo1(ALU_add));
    ALUCommands.emplace(49, foo1(ALU_sub));
    ALUCommands.emplace(50, foo1(ALU_divide));
    ALUCommands.emplace(51, foo1(ALU_mul));

}

int ALU_add(int value)
{
    translationToAdditionalCode(&accumulator);
    translationToAdditionalCode(&value);
    
    int result = accumulator + value;
    if (result == 24576)
    {
        sc_regSet(OVERFLOW, 1);
        return -1;
    }

    translationToStraightCode(&result);
    result &= 0b111111111111111;
    accumulator = result;

    return 0;
}
int ALU_sub(int value)
{
    if (((value >> 13) & 0b1) == 1)
    {
        value &= 0b101111111111111;
    }
    else if ((value & 0b1111111111111) == 0)
    {

    }
    else
    {
        value |= (0b1 << 13);
    }
    ALU_add(value);

    return 0;
}
int ALU_divide(int value)
{
    if ((value & 0b1111111111111) == 0)
    {
        sc_regSet(DIVISION_ZERO, 1);
        return -1;
    }
    int sign = 0;
    if (((accumulator >> 13) == 0b11)  || (accumulator < value))
    {
        accumulator &= 0b101111111111111;
        sign++;
    }
    if ((value >> 13) == 0b11)
    {
        value &= 0b101111111111111;
        sign++;
    }

    int result = 0;

    while (true)
    {
        if (accumulator < value)
            break;

        result++;

        ALU_sub(value);
    }

    if (sign == 1)
        result |= 0b010000000000000;
    accumulator = result | 0b100000000000000;

    return 0;
}
int ALU_mul(int value)
{
    int sign = 0;
    if ((accumulator >> 13) == 0b11)
    {
        accumulator &= 0b101111111111111;
        sign++;
    }
    if ((value >> 13) == 0b11)
    {
        value &= 0b101111111111111;
        sign++;
    }

    int temp = accumulator;
    for (int i = 0; i < (value & 0b1111111111111) - 1; i++)
        if (ALU_add(temp) == -1)
            return -1;

    if (sign == 1)
        accumulator |= 0b010000000000000;

    return 0;
}

int ALU(int command, int operand)
{
    int value;
    if (sc_memoryGet(operand, &value) == -1)
        return -1;
    if (ALUCommands[command](value) == -1)
        return -1;
    
    return 0;
}