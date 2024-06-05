#include "circular_buffer.h"

#include <limits.h>

static int32_t * circular_buffer;
static size_t circular_buffer_size;
static uint32_t tail;
static uint32_t head;

void circularBufferInit(int32_t * buffer, size_t buffer_size) {
    circular_buffer = buffer;
    circular_buffer_size = buffer_size;
    tail = 0u;
    head = 0u;
}

int32_t circularBufferGet(void) {
    int32_t ret = 0;

    if (tail == head) {
        ret = INT_MAX;
    }
    else {
        ret = circular_buffer[tail];
        tail = (tail + 1) % circular_buffer_size;
    }

    return ret;
}

void circularBufferInsert(int32_t value) {
    circular_buffer[head] = value;
    head = (head + 1) % circular_buffer_size;
}

