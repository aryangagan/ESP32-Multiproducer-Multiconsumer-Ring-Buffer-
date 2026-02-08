#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdint.h>
#include <stdbool.h>

#define RINGBUF_SIZE 16   // small on purpose

typedef struct {
    uint8_t buffer[RINGBUF_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} ringbuf_t;

/* API */
void ringbuf_init(ringbuf_t *rb);
bool ringbuf_push(ringbuf_t *rb, uint8_t data);
bool ringbuf_pop(ringbuf_t *rb, uint8_t *data);

#endif