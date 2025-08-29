#ifndef RING_BUFFER_H
# define RING_BUFFER_H

#include <stdint.h>
#include <stdlib.h>

typedef struct s_rb
{
	uint8_t		*buffer;
	size_t		head;
	size_t		tail;
	size_t		maxlen;
} t_rb;

int		rb_push(t_rb *c, uint8_t data);
int		rb_pop(t_rb *c, uint8_t *data);
void	rb_init(t_rb *c, size_t size);
void	rb_clean(t_rb *c);

#endif
