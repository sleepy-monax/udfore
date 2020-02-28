#pragma once

#include "udfore/utils/Utils.h"

struct Source;

typedef char (*SourceNextCharCallback)(struct Source *source);
typedef void (*SourceDestroyCallback)(struct Source *source);
typedef bool (*SourceIsEOFCallback)(struct Source *source);

typedef struct Source
{
    char peeked_char;
    char current_char;

    SourceDestroyCallback destroy;
    SourceNextCharCallback next_char;
    SourceIsEOFCallback is_EOF;
} Source;

#define SOURCE(__subclass) ((Source *)(__subclass))

void source_initialize(Source *source);

Source *file_source_create(const char *path);

Source *string_source_create(const char *source_code, size_t lenght);

void source_destroy(Source *source);

void source_next_char(Source *source);

bool source_is_EOF(Source *source);

char source_current_char(Source *source);

char source_peek_char(Source *source);
