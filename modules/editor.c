#include "../core/include/main.h"

/**
 * process_keypress - parsing type inputs
 * Return: void - nothing
 */
void process_keypress()
{
	int ch, times;

	ch = read_key();
	switch(ch)
	{
	case CNTRL_KEY('q'):
		write(STDIN_FILENO, "\x1b[2J", 4);
		write(STDIN_FILENO, "\x1b[H", 3);
		exit(0);
		break;
	case HOME_KEY: E.cx = 0;
		break;
	case END_KEY: E.cx = E.screencols - 1;
		break;
	case ARROW_UP:
	case ARROW_DOWN:
	case ARROW_RIGHT:
	case ARROW_LEFT:
		move_cursor(ch);
		break;
	case PAGE_UP:
	case PAGE_DOWN:
		times = E.screenrows;
		while (times--) move_cursor(ch == PAGE_UP ? ARROW_UP : ARROW_DOWN);
		break;
	}
}

/**
 * read_key - wait and read for one char per call
 * Return: char read
 */
int read_key()
{
	int num;
	char ch, seq[3];

	while ((num = read(STDIN_FILENO, &ch, 1) != 1))
	{
		if (num == -1 && errno != EAGAIN) die("read");
	}

	if (ch == '\x1b')
	{
		if ((read(STDIN_FILENO, &seq[0], 1) != 1)) return '\x1b';
		if ((read(STDIN_FILENO, &seq[1], 1) != 1)) return '\x1b';
		if (seq[0] == '[')
		{
			if (seq[1] >= '0' && seq[1] <= '9')
			{
				if ((read(STDIN_FILENO, &seq[2], 1) != 1)) return '\x1b';
				if (seq[2] == '~')
				{
					switch(seq[1])
					{
					case '1': return HOME_KEY;
					case '3': return DEL_KEY;
					case '4': return END_KEY;
					case '5': return PAGE_UP;
					case '6': return PAGE_DOWN;
					case '7': return HOME_KEY;
					case '8': return END_KEY;
					}
				}
			}
			switch (seq[1])
			{
			case 'A': return ARROW_UP;
			case 'B': return ARROW_DOWN;
			case 'C': return ARROW_RIGHT;
			case 'D': return ARROW_LEFT;
			case 'H': return HOME_KEY;
			case 'F': return END_KEY;
			}
		}
		else if (seq[0] == 'O')
		{
			switch (seq[1])
			{
			case 'H': return HOME_KEY;
			case 'F': return END_KEY;
			}
		}
		return '\x1b';
	}

	return ch;
}

/**
 * clear_screen - erase everything on the screen
 * Return: void - nothing
 */
void clear_screen()
{
	char buf[32];
	struct buffer ab = BUFF_INIT;

	scroll();
	append_buffer(&ab, "\x1b[?25l", 6);
	append_buffer(&ab, "\x1b[H", 3);
	draw_rows(&ab);
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH",
		 (E.cy - E.rowoff) + 1, (E.rx - E.coloff) + 1);
	append_buffer(&ab, buf, strlen(buf));
	append_buffer(&ab, "\x1b[?25h", 6);
	write(STDIN_FILENO, ab.buff, ab.len);
	buffer_free(&ab);
}

/**
 * scroll - setup cursor location when moving off the screen
 * Return: void - nothing
 */
void scroll()
{
	E.rx = 0;
	if (E.cy < E.numrows) E.rx = row_cx_to_rx(&E.row[E.cy], E.cx);
	if (E.cy < E.rowoff) E.rowoff = E.cy;
	if (E.cy > E.rowoff + E.screenrows + 1) E.rowoff = E.cy - E.screenrows + 1;
	if (E.rx < E.coloff) E.coloff = E.rx;
	if (E.rx > E.coloff + E.screencols + 1) E.coloff = E.rx - E.screencols + 1;
}


/**
 * move_cursor - move cursor in the editior
 * @ch: the direction to move
 * Return: void - nothing
 */
void move_cursor(int c)
{
	int len;
	erow *row = (E.cy > E.numrows) ? NULL : &E.row[E.cy];
	switch(c)
	{
	case ARROW_UP: if (E.cy) E.cy--;
		break;
	case ARROW_DOWN: if (E.cy < E.numrows) E.cy++;
		break;
	case ARROW_RIGHT:
		if (row && E.cx < row->size) E.cx++;
		else if (row && E.cx == row->size)
		{
			E.cy++;
			E.cx = 0;
		}
		break;
	case ARROW_LEFT:
		if (E.cx) E.cx--;
		else if (E.cy > 0)
		{
			E.cy--;
			E.cx = E.row[E.cy].size;
		}
		break;
	}

	row = (E.cy > E.numrows) ? NULL : &E.row[E.cy];
	len =  row ? row->size : 0;
	if (E.cx > len) E.cx = len;
}
