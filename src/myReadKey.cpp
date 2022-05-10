#include "myReadKey.h"

termios savedAttributes;

int rk_readKey(int mode)
{
	rk_saveTerminalSetup();

	rk_switchMode(mode);

	char buf[6] = { 0 };

	read(STDIN_FILENO, buf, 6);

	if (mode == 1)
	{
		auto it = commandsTerminal.find(buf);

		if (it != commandsTerminal.end())
		{
			it->second();
		}	
	}
	else if (mode == 0)
	{
		return atoi(buf);
	}

	rk_restoreTerminalSetup();

	return 0;
}

int rk_saveTerminalSetup()
{
	tcgetattr(STDIN_FILENO, &savedAttributes);

	return 0;
}

int rk_restoreTerminalSetup()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &savedAttributes);

	return 0;
}

int rk_switchMode(int mode)
{
	termios tempAttributes;

	tcgetattr(STDIN_FILENO, &tempAttributes);

	if (mode == 1) // canonical
	{
		tempAttributes.c_lflag &= ~(ICANON); // off ICANON
	}
	else if (mode == 0)
	{
		tempAttributes.c_lflag |= ICANON;
	}
	else
	{
		return -1;
	}

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tempAttributes);

	return 0;
}

