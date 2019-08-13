#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

size_t utils_get_file_size(FILE *file)
{
    assert(file);
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    return size;
}

bool utils_is_white_space(char chr)
{
    return chr == ' ' || chr == '\n' || chr == '\r' || chr == '\t';
}

bool utils_is_letter(char chr)
{
    return (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z');
}

bool utils_is_number(char chr)
{
    return (chr >= '0' && chr <= '9');
}