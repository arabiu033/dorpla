#include "../core/include/main.h"

/**
 * draw_status_bar - create a status bar
 * @ab: the editor buffer
 * Return: void
 */
void draw_status_bar(struct buffer *ab)
{
	int len, rlen;
	char status[80], rstatus[80];

	append_buffer(ab, "\x1b[7m", 4);
	len = snprintf(status, sizeof(status), "%.20s - %d lines",
		       E.filename ? E.filename : "[No Name]", E.numrows);
	rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", E.cy + 1, E.numrows);
	if (len > E.screencols) len = E.screencols;
	append_buffer(ab, status, len);
	while (len < E.screencols)
	{
		if (E.screencols - len == rlen)
		{
			append_buffer(ab, rstatus, rlen);
			break;
		}
		append_buffer(ab, " ", 1);
		len++;
	}
	append_buffer(ab, "\x1b[m", 3);
	append_buffer(ab, "\r\n", 2);
}

/**
 * status_msg - display the current editior status message
 * @fmt: the first argument to disable
 * Return: void - nothing
 */
void status_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
	va_end(ap);
	E.statusmsg_time = time(NULL);
}


/**
 * draw_msg_bar - create a message area
 * @ab: the editor buffer
 * Return: void - nothing
 */
void draw_msg_bar(struct buffer *ab)
{
	int len = 0;
	append_buffer(ab, "\x1b[k", 3);
	len = strlen(E.statusmsg);
	if (len > E.screencols) len = E.screencols;
	if (len && difftime(E.statusmsg_time, time(NULL)) < 5)
		append_buffer(ab, E.statusmsg, len);
}
