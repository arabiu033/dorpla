#include "../core/include/main.h"

/**
 * open - open files and read data
 * @file: the file to open
 * Return: void - nothing
 */
void open(char *file)
{
	FILE *fp = fopen(file, "r");
	char *line = NULL;
	size_t cap;
	ssize_t len;

	if (!fp) die("fopen");
	while ((len = getline(&line, &cap, fp)) != -1)
	{
		while(len > 0 && (line[len - 1] == '\n' ||
				  line[len - 1] == '\r'))
			len--;
		append_row(line, len);
	}
	free(line);
	fclose(fp);
}


/**
 * append_row - append the next line read from a file
 * @s: the line to append
 * @len: the len of the file
 * Return: void nothing
 */
void append_row(char *s, size_t len)
{
	int at = E.numrows;

	E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
	E.row[at].size = len;
	E.row[at].line = malloc(len + 1);
	memcpy(E.row[at].line, s, len);
	E.row[at].line[len] = '\0';
	E.numrows++;
	E.row[at].rsize = 0;
	E.row[at].render = NULL;
	update_row(&E.row[at]);
}

/**
 * update_row - handle row with special characters like tabs
 * @row: the row to handle
 * Return: void - nothing
 */
void update_row(erow *row)
{
	int i, indx, tabs = 0;
	for (i = 0; i < row->size; i++)
	{
		if (row->line[i] == '\t') ++tabs;
	}
	free(row->render);
	row->render = malloc(row->size + tabs * (TAB_STOP - 1) + 1);
	indx = 0;
	for (i = 0; i < row->size; i++)
	{
		if (row->line[i] == '\t')
		{
			row->render[indx++] = ' ';
			while (indx % TAB_STOP) row->render[indx++] = ' ';
		}
		else row->render[indx++] = row->line[i];
	}

	row->render[indx] = '\0';
	row->rsize = indx;
}

/**
 * row_cx_to_rx - calculate the cursor position taking tabs into account
 * @row: the current row to calculate
 * @cx: the current cursor positon
 * Return: the new size inluding tabs spaces
 */
int row_cx_to_rx(erow *row, int cx)
{
	int i, rx = 0;
	for (i = 0; i < cx; i++)
	{
		if (row->line[i] == '\t')
		{
			rx += (TAB_STOP - 1) - (rx % TAB_STOP);
		}
		++rx;
	}

	return (rx);
}
