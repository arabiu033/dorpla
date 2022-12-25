#include "../include/main.h"

/**
 * main - entry point of our project
 * Return: 0 - success
 */
int main()
{
	char ch;

	enable_raw_mode();
	while(1)
	{
		ch = '\0';
		if (read(STDIN_FILENO, &ch, 1) == -1 && errno != EAGAIN) die("read");
		iscntrl(ch) ? printf("%d\r\n", ch) : printf("%d ('%c')\r\n", ch, ch);
		if (ch == 'q') break;
	}
	return (0);
}
