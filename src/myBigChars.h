#pragma once

#include <iostream>

#include "myTerm.h"
#include "enumColors.h"

#define RIGHT_BOTTOM_ANGLE 'j'
#define RIGHT_TOP_ANGLE 'k'
#define LEFT_BOTTOM_ANGLE 'm'
#define LEFT_TOP_ANGLE 'l'
#define HORIZONTAL_LINE 'q'
#define VERTICAL_LINE 'x'
#define FILL 'a'

int bc_printSpecialChar (char str);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printBigChar (long myChar, int x, int y, colors fgColor, colors bgColor);
int bc_setBigCharPos (int* big, int x, int y, int value);
int bc_getBigCharPos (int* big, int x, int y, int* value);
int bc_bigCharWrite (int fd, int* big, int count);
int bc_bigCharRead (int fd, int* big, int need_count, int* count);

