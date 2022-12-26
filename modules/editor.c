#include "../core/include/main.h"

/**
 * process_keypress - parsing type inputs
 * Return: void - nothing
 */
void process_keypress()
{
	char ch;

	ch = read_key();
	switch(ch)
	{
	case CNTRL_KEY('q'):
		write(STDIN_FILENO, "\x1b[2J", 4);
		write(STDIN_FILENO, "\x1b[H", 3);
		exit(0);
		break;
	}
}

/**
 * read_key - wait and read for one char per call
 * Return: char read
 */
char read_key()
{
	int num;
	char ch;

	while ((num = read(STDIN_FILENO, &ch, 1) != 1))
	{
		if (num == -1 && errno != EAGAIN) die("read");
	}

	return ch;
}

/**
 * clear_screen - erase everything on the screen
 * Return: void - nothing
 */
void clear_screen()
{
	struct buffer ab = BUFF_INIT;

	append_buffer(&ab, "\x1b[?25l", 6);
	append_buffer(&ab, "\x1b[2J", 4);
	append_buffer(&ab, "\x1b[H", 3);
	draw_rows(&ab);
	append_buffer(&ab, "\x1b[H", 3);
	append_buffer(&ab, "\x1b[?25h", 6);
	write(STDIN_FILENO, ab.buff, ab.len);
	buffer_free(&ab);
}
