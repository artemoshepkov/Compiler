#include "viewInterface.h"

int LEFT_TOP_ANGLE_INTERFACE = 1;

int WIDTH_BOX_MEMORY = 62;

char DigitToHex(int N)
{
  switch (N)
  {
    case 0  : return('0'); break;
    case 1  : return('1'); break;
    case 2  : return('2'); break;
    case 3  : return('3'); break;
    case 4  : return('4'); break;
    case 5  : return('5'); break;
    case 6  : return('6'); break;
    case 7  : return('7'); break;
    case 8  : return('8'); break;
    case 9  : return('9'); break;
    case 10 : return('A'); break;
    case 11 : return('B'); break;
    case 12 : return('C'); break;
    case 13 : return('D'); break;
    case 14 : return('E'); break;
    case 15 : return('F'); break;
    default : return('?');
  }
}
std::string MyIntToHex(int Num, int Count = 4)
{
  std::string Res = "?";
  if (Num < 0) return(Res);
  Res = "";
  int N = Num;
  int i = 1;
  int X;
  while (N > 0)
  {
    i++;
    X = N % 16;
    N = N / 16;
    if (X < 16) Res = DigitToHex(X) + Res;
  }
  for (int j = i; j <= Count; j++) 
  	Res = '0' + Res;
  
  return(Res);
}    

int in_printInterface()
{
	in_printMemory(LEFT_TOP_ANGLE_INTERFACE);
	in_printAccumulator(LEFT_TOP_ANGLE_INTERFACE + WIDTH_BOX_MEMORY, LEFT_TOP_ANGLE_INTERFACE);
	in_printInstructionCounter(LEFT_TOP_ANGLE_INTERFACE + WIDTH_BOX_MEMORY, LEFT_TOP_ANGLE_INTERFACE + 3);
	in_printOperation(LEFT_TOP_ANGLE_INTERFACE + WIDTH_BOX_MEMORY, LEFT_TOP_ANGLE_INTERFACE + 6);
	in_printFlags(LEFT_TOP_ANGLE_INTERFACE + WIDTH_BOX_MEMORY, LEFT_TOP_ANGLE_INTERFACE + 9);
	in_printBigChars(instructionCounter, LEFT_TOP_ANGLE_INTERFACE, LEFT_TOP_ANGLE_INTERFACE + 12);
	in_printKeys(LEFT_TOP_ANGLE_INTERFACE + 46, LEFT_TOP_ANGLE_INTERFACE + 12);	
	in_terminal(LEFT_TOP_ANGLE_INTERFACE, LEFT_TOP_ANGLE_INTERFACE + 22);

	mt_gotoXY(30, 1);

	return 0;
}

int in_printMemory(int leftTopAngle)
{
	int height = 12;
	
	bc_box(leftTopAngle, leftTopAngle, WIDTH_BOX_MEMORY + leftTopAngle, height + leftTopAngle);

	mt_gotoXY(leftTopAngle, WIDTH_BOX_MEMORY / 2);
	std::cout << "Memory";
        
	mt_gotoXY(leftTopAngle + 1, leftTopAngle + 1);
	

	int valueMemory;
	for (int i = 1; i < SIZEARRAYMEMORY + 1; i++)
	{	
		sc_memoryGet(i - 1, &valueMemory);
	
		if (i - 1 == instructionCounter)
		{
			mt_setFgColor(black);
			mt_setBgColor(white);
		}
		
		if (sc_verifyCommand(valueMemory))
			std::cout << "+";
		else 
			std::cout << " ";
		
		std::cout << std::setfill('0') << std::setw(4);
		std::cout << MyIntToHex(valueMemory);

		if (i - 1 == instructionCounter)
		{
			mt_setFgColor(white);
			mt_setBgColor(black);
		}

		if (i % 10 == 0)
			mt_gotoXY(leftTopAngle + 1 + i / 10 , leftTopAngle + 1);
		else
			std::cout << " ";	
	}

	return 0;
}

int in_printAccumulator(int leftTopAngleX, int leftTopAngleY)
{
	int width = 22;
	int height = 3;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 5);
	std::cout << "accumulator";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 8);
	if (sc_verifyCommand(accumulator))
		std::cout << "+";
	else 
		std::cout << " ";
	std::cout << std::setfill('0') << std::setw(4);
	std::cout << MyIntToHex(accumulator);

	return 0;
}

int in_printInstructionCounter(int leftTopAngleX, int leftTopAngleY)
{
	int width = 22;
	int height = 3;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 2);
	std::cout << "instructionCounter";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 8);
	std::cout << std::setfill('0') << std::setw(4);
	std::cout << MyIntToHex(instructionCounter);

	return 0;
}

int in_printOperation(int leftTopAngleX, int leftTopAngleY)
{
	int width = 22;
	int height = 3;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 8);
	std::cout << "operation";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 8);

	if (sc_verifyCommand(arrayMemory[instructionCounter]))
	{
		std::cout << std::hex << (arrayMemory[instructionCounter] >> 7) << " : " << (arrayMemory[instructionCounter] & 127) << std::dec;
	}
	return 0;
}
int in_terminal(int leftTopAngleX, int leftTopAngleY)
{
	int width = 22;
	int height = 3;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 8);
	std::cout << "Terminal";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 8);

	if (((terminal >> 13) & 0b1) == 1)
		std::cout << "-";
	terminal &= 0b1111111111111;

	std::cout << terminal;

	return 0;
}
int in_printFlags(int leftTopAngleX, int leftTopAngleY)
{
	int width = 22;
	int height = 3;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 8);
	std::cout << "Flags";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 8);

	if (sc_regGet(OVERFLOW))
		std::cout << "0";
	if (sc_regGet(DIVISION_ZERO))
		std::cout << "D";
	if (sc_regGet(OUT_OF_MEMORY))
		std::cout << "M";
	if (sc_regGet(IGNORE_TACTS))
		std::cout << "I";
	if (sc_regGet(WRONG_COMMAND))
		std::cout << "E";

	return 0;
}

int in_printKeys(int leftTopAngleX, int leftTopAngleY)
{
	int width = 38;
	int height = 10;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	mt_gotoXY(leftTopAngleY, leftTopAngleX + 2);
	std::cout << "Keys";

	mt_gotoXY(leftTopAngleY + 1, leftTopAngleX + 1);
	std::cout << "l - load";

	mt_gotoXY(leftTopAngleY + 2, leftTopAngleX + 1);
	std::cout << "s - save";

	mt_gotoXY(leftTopAngleY + 3, leftTopAngleX + 1);
	std::cout << "r - run";

	mt_gotoXY(leftTopAngleY + 4, leftTopAngleX + 1);
	std::cout << "t - step";

	mt_gotoXY(leftTopAngleY + 5, leftTopAngleX + 1);
	std::cout << "i - reset";

	mt_gotoXY(leftTopAngleY + 6, leftTopAngleX + 1);
	std::cout << "F5 - accumulator";

	mt_gotoXY(leftTopAngleY + 7, leftTopAngleX + 1);
	std::cout << "F6 - instructionCounter";

	return 0;
}

int in_printBigChars(int index, int leftTopAngleX, int leftTopAngleY)
{
	int width = 46;
	int height = 10;

	bc_box(leftTopAngleX, leftTopAngleY, width + leftTopAngleX, height + leftTopAngleY);

	if (index < 0 || index > SIZEARRAYMEMORY - 1)
		return -1;

	if (sc_verifyCommand(arrayMemory[index]))
		bc_printBigChar(PLUS, leftTopAngleX + 1, leftTopAngleY + 1, white, black);

	std::string hexMemoryElement = MyIntToHex(arrayMemory[index]); 
	mt_gotoXY(100, 1);
	int countBigNumbers = 5;
	for (int i = 1; i < countBigNumbers; i++)
	{	
		switch(hexMemoryElement[i - 1])
		{
			case '0':
				bc_printBigChar(ZERO, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '1':
				bc_printBigChar(ONE, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '2':
				bc_printBigChar(TWO, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '3':
				bc_printBigChar(THREE, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '4':
				bc_printBigChar(FOUR, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '5':
				bc_printBigChar(FIVE, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '6':
				bc_printBigChar(SIX, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '7':
				bc_printBigChar(SEVEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '8':
				bc_printBigChar(EIGHT, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case '9':
				bc_printBigChar(NINE, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'A':
				bc_printBigChar(TEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'B':
				bc_printBigChar(ELEVEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'C':
				bc_printBigChar(TWELVE, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'D':
				bc_printBigChar(THIRTEEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'E':
				bc_printBigChar(FOURTEEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			case 'F':
				bc_printBigChar(FIFTEEN, leftTopAngleX + 1 + i * 9, leftTopAngleY + 1, white, black);
				break;
			default:
				std::cout << "ERROR";
		}	
	}
	return 0;
}
