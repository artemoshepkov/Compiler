#include "myBigChars.h"

int bc_printSpecialChar (char str)
{
	std::cout << "\E(0" << str << "\E(B";
	return 0;
}

int bc_box (int x1, int y1, int x2, int y2)
{	
	int width = x2 - x1;
	int height = y2 - y1;

	if (width < 2 || height < 2)
		return -1;

	mt_gotoXY(y1, x1);
	bc_printSpecialChar(LEFT_TOP_ANGLE);
	for (int i = 0; i < width - 2; i++)
	       bc_printSpecialChar(HORIZONTAL_LINE);
	bc_printSpecialChar(RIGHT_TOP_ANGLE);


	for (int i = 1; i < height - 1; i++)
	{
		mt_gotoXY(y1 + i, x1);
		bc_printSpecialChar(VERTICAL_LINE);
		mt_gotoXY(y1 + i, x2 - 1);
		bc_printSpecialChar(VERTICAL_LINE);
	}

	mt_gotoXY(y2 - 1, x1);
	bc_printSpecialChar(LEFT_BOTTOM_ANGLE);
	for (int i = 0; i < width - 2; i++)
		bc_printSpecialChar(HORIZONTAL_LINE);
	bc_printSpecialChar(RIGHT_BOTTOM_ANGLE);

	return 0;
}

int bc_printBigChar (long myChar, int x, int y, colors fgColor, colors bgColor)
{
	mt_setFgColor(fgColor);
	mt_setBgColor(bgColor);
	
	unsigned long mask = 0X8000000000000000;
	
	mt_gotoXY(y, x);
	for (int i = 1; i < 65; i++)
	{
		if ((mask & myChar) == 0l)
	       		std::cout << " ";
		else
			bc_printSpecialChar(FILL);
		if (i % 8 == 0)
			mt_gotoXY(y + (i / 8), x);

		mask >>= 1;
	}


	return 0;
}

int bc_setBigCharPos (long* big, int x, int y, int value) 
{
	unsigned long mask = 0x8000000000000000;
	for (int i = 0; i < y; i++)
		mask >>= 10000000;
	for (int i = 0; i < x; i++)
		mask >>= 1;

	if (value == 0)
	{
		*big &= ~mask;			
	}
	else if (value == 1)
	{
		*big |=	mask;	
	}
	else
	{	
		return -1;
	}

	return 0;
}

int bc_getBigCharPos (long big, int x, int y, int* value)
{
	unsigned long mask = 0x8000000000000000;
	
	for (int i = 0; i < y; i++)
		mask >>= 10000000;
	for (int i = 0; i < x; i++)
		mask >>= 1;

	*value = (big & mask);
	if (*value > 1)
		*value = 1;

	return 0;
}
