#include "../core/include/main.h"

/**
 * get_win_size - obtain the size of the user window
 * @row: size of row
 * @col: size of col
 * Return: the size
 */
int get_win_size(int *row, int *col)
{
	struct winsize ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		if (write(STDIN_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return (-1);
		return get_cursor_pos(row, col);
	}
	*row = ws.ws_row;
	*col = ws.ws_col;
	return (0);
}

/**
 * draw_rows - draw tilde on the editior screen
 * Return: void - nothing
 */
void draw_rows(struct buffer *ab)
{
	int x, padding;

	for (x = 0; x < E.screenrows; x++)
	{
		if (x >= E.numrows)
		{
			if (!E.numrows && x == E.screenrows / 3)
			{
				char welcome[80];
				int welcomelen = snprintf(welcome, sizeof(welcome),
							  "Durpla editor -- version %s", VERSION);
				if (welcomelen > E.screencols) welcomelen = E.screencols;
				padding = (E.screencols - welcomelen) / 2;
				if (padding)
				{
					append_buffer(ab, "~", 1);
					padding--;
				}
				while (padding--) append_buffer(ab, " ", 1);
				append_buffer(ab, welcome, welcomelen);
			}
			else append_buffer(ab, "~", 1);
		}
		else
		{
			int len = E.row[x].size;
			if (len > E.screencols) len = E.screencols;
			append_buffer(ab, E.row[x].line, len);
		}
		append_buffer(ab, "\x1b[K", 4);
		if ( x < E.screenrows - 1)
			append_buffer(ab, "\r\n", 2);
	}
}


/**
 * init_editior - call getwinsize method before doing anything
 * Return: void - nothing
 */
void init_editor()
{
	E.cx = 0;
	E.cy = 0;
	E.numrows = 0;
	E.row = NULL;
	if (get_win_size(&E.screenrows, &E.screencols) == -1) die("getWinSize");
}

/**
 * get_cursor_pos - obtain the position of cursor on the terminal
 * @row: row coordinate
 * @col: col corordinatye
 * Return: 0 - success
 */
int get_cursor_pos(int *rows, int *cols)
{
	char buf[32];
	unsigned int i = 0;

	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
		if (buf[i] == 'R') break;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[') return -1;
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
	return 0;
}
