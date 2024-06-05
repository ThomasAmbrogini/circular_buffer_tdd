#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h>
#include <stdint.h>

void circularBufferInit(int32_t * buffer, size_t buffer_size);
int32_t circularBufferGet(void);
void circularBufferInsert(int32_t value);

#endif /* __CIRCULAR_BUFFER_H__ */

