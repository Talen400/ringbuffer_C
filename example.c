#include <stdio.h>
#include "ring_buffer.h"

#define BUFFER_SIZE 32

int main (void)
{
	t_rb	rb;
	uint8_t	data;

	rb_init(&rb, 5);
	// examples
	rb_push(&rb, 10);
	rb_push(&rb, 20);
	while (rb_pop(&rb, &data) != -1)
		printf("Popped: %d\n", data);
	rb_clean(&rb);
	return (0);
}
