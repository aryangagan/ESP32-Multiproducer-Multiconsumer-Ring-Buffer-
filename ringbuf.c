#include "ringbuf.h"

void ringbuf_init(ringbuf_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

bool ringbuf_push(ringbuf_t *rb, uint8_t data)
{
    if (rb->count == RINGBUF_SIZE) {
        return false; // buffer full
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % RINGBUF_SIZE;
    rb->count++;
    return true;
}

bool ringbuf_pop(ringbuf_t *rb, uint8_t *data)
{
    if (rb->count == 0) {
        return false; // buffer empty
    }

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RINGBUF_SIZE;
    rb->count--;
    return true;
}