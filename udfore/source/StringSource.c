#include <assert.h>
#include <string.h>

#include "udfore/source/Source.h"

typedef struct
{
    Source source;

    size_t offset;
    size_t lenght;
    char *buffer;
} StringSource;

void string_source_destroy(StringSource *source)
{
    free(source->buffer);
}

char string_source_next_char(StringSource *source)
{
    assert(source->offset <= source->lenght);
    char chr = source->buffer[source->offset];
    source->offset++;

    return chr;
}

bool string_source_is_EOF(StringSource *source)
{
    return !(source->offset < source->lenght);
}

Source *string_source_create(const char *source_code, size_t lenght)
{
    StringSource *source = __create(StringSource);

    char *buffer = calloc(lenght, sizeof(char));
    memcpy(buffer, source_code, lenght);

    source->buffer = buffer;
    source->lenght = lenght;
    source->offset = 0;

    SOURCE(source)->destroy = (SourceDestroyCallback)string_source_destroy;
    SOURCE(source)->next_char = (SourceNextCharCallback)string_source_next_char;
    SOURCE(source)->is_EOF = (SourceIsEOFCallback)string_source_is_EOF;

    source_initialize(SOURCE(source));

    return SOURCE(source);
}