#include "ALU.h" 

std::map <int, foo1> ALUCommands;
    //     case 81:
    //         break;
    //     case 82:
    //         break;
    //     case 83:
    //         break;
    //     case 84:
    //         break;
    //     case 85:
    //         break;
    //     case 86:
    //         break;
    //     case 87:
    //         break;
    //     case 88:
    //         break;
    //     case 89:
    //         break;
    //     case 96:
    //         break;
    //     case 97:
    //         break;
    //     case 98:
    //         break;
    //     case 99:
    //         break;
    //     case 100:
    //         break;
    //     case 101:
    //         break;
    //     case 102:
    //         break;
    //     case 103:
    //         break;
    //     case 104:
    //         break;
    //     case 105:
    //         break;
    //     case 112:
    //         break;
    //     case 113:
    //         break;
    //     case 114:
    //         break;
    //     case 115:
    //         break;
    //     case 116:
    //         break;
    //     case 117:
    //         break;
    //     case 118:

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