#include "udfore/source/Source.h"

void source_destroy(Source *source)
{
    if (source->destroy)
    {
        source->destroy(source);
    }

    free(source);
}

void source_next_char(Source *source)
{
    if (source_is_EOF(source))
    {
        source->current_char = source->peeked_char;
        source->peeked_char = EOF;
    }
    else
    {
        source->current_char = source->peeked_char;
        source->peeked_char = source->next_char(source);
    }
}

bool source_is_EOF(Source *source)
{
    return source->is_EOF(source);
}

char source_current_char(Source *source)
{
    return source->current_char;
}

char source_peek_char(Source *source)
{
    return source->peeked_char;
}

void source_initialize(Source *source)
{
    source_next_char(source);
    source_next_char(source);
}
