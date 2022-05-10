#include "myTerm.h"

int mt_gotoXY(int x, int y)
{
	if (x < 0 || y < 0)
		return -1;

	std::cout << "\E[" << x << ";" << y << "H"; 	
	return 0;
}

int mt_clrScr()
{
	std::cout << "\E[H\E[J";
	mt_gotoXY(0, 0);
	return 0;
}

int mt_setFgColor(colors color)
{
	if (color < 0 || color > 7)
		return -1;
	
	std::cout << "\E[3" << color << "m";
	return 0;
}


int mt_setBgColor(colors color)
{
	if (color < 0 || color > 7)
		return -1;

	std::cout << "\E[4" << color << "m";
	return 0;
}

int mt_getScreenSize(int* rows, int* cols)
{
	struct winsize ws;

	if (!ioctl(1, TIOCGWINSZ, &ws))
	{
		*rows = ws.ws_row;
		*cols = ws.ws_col;
		return 0;
	}

	return -1;
}
