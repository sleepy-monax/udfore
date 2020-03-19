#include <inttypes.h>

#include "udfore/value/Value.h"

void value_serialize(Value value, Buffer *buffer)
{
    switch (value.type)
    {
    case VALUE_S32:
    {
        char b[14];
        sprintf(b, "%" PRId32, value.s32);

        buffer_append_str(buffer, b);
    }
    break;

    default:
        buffer_append_str(buffer, "<none-type>");
        break;
    }
}

Value value_create_s32(int32_t s32)
{
    return (Value){VALUE_S32, {.s32 = s32}};
}
