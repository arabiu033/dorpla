#include "../include/main.h"

/**
 * main - entry point of our project
 * Return: 0 - success
 */
int main()
{
	enable_raw_mode();
	init_editor();
	while(1)
	{
		clear_screen();
		process_keypress();
	}
	return (0);
}
