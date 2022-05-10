#pragma once

#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <iostream>

#include "CommandInterface.h"

extern termios savedAttributes;

int rk_readKey(int mode);
int rk_saveTerminalSetup();
int rk_restoreTerminalSetup();
int rk_switchMode(int mode);
