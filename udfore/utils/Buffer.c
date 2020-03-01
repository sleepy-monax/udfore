#include "udfore/utils/Buffer.h"

Buffer *buffer_create(size_t preallocated)
{
    Buffer *buffer = __create(Buffer);

    buffer->buffer = calloc(preallocated, sizeof(char));
    buffer->size = preallocated;
    buffer->used = 0;

    return buffer;
}

void buffer_destroy(Buffer *buffer)
{
    if (buffer->buffer)
    {
        free(buffer->buffer);
    }

    free(buffer);
}

char *buffer_finalize(Buffer *buffer)
{
    char *result = buffer->buffer;
    buffer->buffer = NULL;

    buffer_destroy(buffer);

    return result;
}

void buffer_append_str(Buffer *buffer, const char *str)
{
    for (size_t i = 0; str[i]; i++)
    {
        buffer_append_chr(buffer, str[i]);
    }
}

void buffer_append_chr(Buffer *buffer, char chr)
{
    if (buffer->used + 1 == buffer->size)
    {
        buffer->size *= 1.25;
        buffer->buffer = realloc(buffer->buffer, buffer->size);
    }

    buffer->buffer[buffer->used] = chr;
    buffer->used++;
}
