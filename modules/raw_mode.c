#include "../core/include/main.h"

/**
 * enable_raw_mode - allow inputs to be processed raw
 * Return: void - nothing
 */
void enable_raw_mode()
{
	struct termios raw;

	if (tcgetattr(STDIN_FILENO, &E.original_termios) == -1) die("tcgetatttr");
	atexit(disable_raw_mode);
	raw = E.original_termios;
	raw.c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= ~(CS8);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/**
 * disable_raw_mode - reset the termial settings back
 * Return: void - nothing
 */
void disable_raw_mode()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.original_termios) == -1)
		die("tcsetattr");
}

/**
 * die - print the error message and exit the program
 * @s: provide the context from where the error comes from
 * Return: void - nothing
 */
void die(const char *s)
{
	write(STDIN_FILENO, "\x1b[2J", 4);
	write(STDIN_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}
