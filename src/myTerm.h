#pragma once

#include "enumColors.h"
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>

int mt_clrScr();
int mt_gotoXY(int x, int y);
int mt_getScreenSize(int* rows, int* cols);
int mt_setFgColor(colors color);
int mt_setBgColor(colors color);
