#pragma once

#include "udfore/utils/Buffer.h"

typedef enum
{
    VALUE_NONE,
    VALUE_S32,
} ValueType;

typedef struct
{
    ValueType type;

    union {
        int32_t s32;
    };
} Value;

void value_serialize(Value value, Buffer *buffer);

Value value_create_s32(int32_t s32);