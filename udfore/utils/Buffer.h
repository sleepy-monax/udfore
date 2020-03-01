#pragma once

#include "udfore/utils/Utils.h"

typedef struct
{
    size_t used;
    size_t size;
    char *buffer;
} Buffer;

Buffer *buffer_create(size_t preallocated);

void buffer_destroy(Buffer *buffer);

char *buffer_finalize(Buffer *buffer);

void buffer_append_str(Buffer *buffer, const char *str);

void buffer_append_chr(Buffer *buffer, char chr);
