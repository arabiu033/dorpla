#include "../core/include/main.h"

/**
 * append_buffer - append strings to our buffer
 * @ab: buffer
 * @s: string to append
 * @len: the string lenght
 */
void append_buffer(struct buffer *ab, const char *s, int len)
{
	char *new = realloc(ab->buff, ab->len + len);

	if (!new) return;

	memcpy(&new[ab->len], s, len);
	ab->buff = new;
	ab->len += len;
}

void buffer_free(struct buffer *ab)
{
	free(ab->buff);
}
