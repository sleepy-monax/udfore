#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "utils.c"

struct source;

typedef void(source_next_char_t)(struct source *this);
typedef void(source_close_t)(struct source *this);

typedef struct source
{
    void *p;
    size_t offset;
    size_t lenght;

    char peeked_char;
    char current_char;

    source_next_char_t *next_char;
    source_next_char_t *close;

    bool is_EOF;
} source_t;

source_t *source(void *from, size_t lenght, source_next_char_t *next_char, source_close_t close)
{
    assert(from != NULL);
    assert(next_char != NULL);
    assert(close != NULL);

    source_t *this = malloc(sizeof(source_t));

    this->p = from;
    this->offset = 0;
    this->lenght = lenght;
    this->is_EOF = false;
    this->next_char = next_char;
    this->close = close;

    this->next_char(this);
    this->next_char(this);

    return this;
}

void source_delete(source_t *this)
{
    this->close(this);
    free(this);
}

void source_from_file_close(source_t *this)
{
    fclose(this->p);
}

void source_from_file_next_char(source_t *this)
{
    if (!this->is_EOF)
    {
        int chr = fgetc(this->p);

        if (chr == EOF)
        {
            this->is_EOF = true;
            chr = 0;
        }

        this->current_char = this->peeked_char;
        this->peeked_char = chr;
    }
    else
    {
        this->current_char = 0;
        this->peeked_char = 0;
    }
}

source_t *source_from_file(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file != NULL)
    {
        return source(
            file,
            utils_get_file_size(file),
            source_from_file_next_char,
            source_from_file_close);
    }

    return NULL;
}

void source_from_string_close(source_t *this)
{
    free(this->p);
}

void source_from_string_next_char(source_t *this)
{
    if (this->offset >= this->lenght)
    {
        this->is_EOF = true;
    }

    if (!this->is_EOF)
    {
        assert(this->offset < this->lenght);
        int chr = ((const char *)this->p)[this->offset];

        if (chr == EOF)
        {
            chr = 0;
        }

        this->current_char = this->peeked_char;
        this->peeked_char = chr;
        this->offset++;
    }
    else
    {
        this->current_char = 0;
        this->peeked_char = 0;
    }
}

source_t *source_from_string(const char *source_code, size_t lenght)
{
    char *str = malloc(lenght);
    memcpy(str, source_code, lenght);

    return source(str, lenght, source_from_string_next_char, source_from_string_close);
}

bool source_is_EOF(source_t *this)
{
    return this->is_EOF;
}

void source_next_char(source_t *this)
{
    assert(this);
    assert(this->next_char);

    this->next_char(this);
}

char source_current_char(source_t *this)
{
    return this->current_char;
}

char source_peek_char(source_t *this)
{
    return this->peeked_char;
}