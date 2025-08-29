#include "ring_buffer.h"

int	rb_push(t_rb *c, uint8_t data)
{
	size_t	next;

	next = c->head + 1;
	if (next >= c->maxlen) // Return to buffer[0]
		next = 0;
	if (next == c->tail) // if haed == tail, return error
		return (-1);
	c->buffer[c->head] = data;
	c->head = next;
	return (0);
}

int	rb_pop(t_rb *c, uint8_t *data)
{
	size_t	next;

	if (c->head == c->tail) // No dato if head == tail, then return error
		return (-1);
	next = c->tail + 1;
	if (next >= c->maxlen) // Return to buffer[0]
		next = 0;
	*data = c->buffer[c->tail];
	c->tail = next;
	return (0);
}

void	rb_init(t_rb *c, size_t size)
{
	c->head = 0;
	c->tail = 0;
	c->maxlen = size;
	c->buffer = (uint8_t *) malloc (size * sizeof(uint8_t ));
}

void	rb_clean(t_rb *c)
{
	if (c->buffer)
		free(c->buffer);
	c->buffer = NULL;
	c->head = 0;
	c->tail = 0;
	c->maxlen = 0;
}
