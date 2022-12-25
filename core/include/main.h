#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>


void enable_raw_mode();
void disable_raw_mode();
void die(const char *);
#endif
