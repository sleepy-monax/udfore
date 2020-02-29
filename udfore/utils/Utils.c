#include "udfore/utils/Utils.h"

bool utils_is_white_space(char chr)
{
    return chr == ' ' || chr == '\n' || chr == '\r' || chr == '\t';
}

bool utils_is_letter(char chr)
{
    return (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z');
}

bool utils_is_identifier(char chr)
{
    return (chr == '_') || utils_is_letter(chr);
}

bool utils_is_number(char chr)
{
    return (chr >= '0' && chr <= '9');
}
