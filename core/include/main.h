#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#define CNTRL_KEY(k) ((k) & 0x1f) /** strip Control keys to their equivalent keys */
#define BUFF_INIT {NULL, 0}

struct config
{
	struct termios original_termios;
	int screenrows;
	int screencols;
};
struct config E;

struct buffer
{
	char *buff;
	int len;
};

void enable_raw_mode();
void disable_raw_mode();
void die(const char *);
void process_keypress();
char read_key();
void clear_screen();
void draw_rows();
int get_win_size(int *, int *);
void init_editor();
int get_cursor_pos(int *, int *);
void append_buffer(struct buffer *, const char *, int);
void buffer_free(struct buffer *);

#endif
