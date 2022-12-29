#include "../include/main.h"

/**
 * main - entry point of our project
 * Return: 0 - success
 */
int main(int argc, char *argv[])
{
	enable_raw_mode();
	init_editor();
	if (argc >= 2) open(argv[1]);
	status_msg("HELP: Ctrl-Q = quit");
	while(1)
	{
		clear_screen();
		process_keypress();
	}
	return (0);
}
