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
}
