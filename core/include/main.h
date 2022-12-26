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
#define VERSION "0.0.1"

struct config
{
	struct termios original_termios;
	int screenrows;
	int screencols;
	int cx, cy;
};
struct config E;

struct buffer
{
	char *buff;
	int len;
};

enum editor_keys
{
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	PAGE_UP,
	PAGE_DOWN,
	HOME_KEY,
	END_KEY,
	DEL_KEY
};

void enable_raw_mode();
void disable_raw_mode();
void die(const char *);
void process_keypress();
int read_key();
void clear_screen();
void draw_rows();
int get_win_size(int *, int *);
void init_editor();
int get_cursor_pos(int *, int *);
void append_buffer(struct buffer *, const char *, int);
void buffer_free(struct buffer *);
void move_cursor(int);

#endif
