#pragma once

typedef struct
{

} utoken_type_t;

typedef struct
{
    utoken_type_t type;
    char* text;
} utoken_t;

typedef enum
{
    UNODE_TYPE_NAMESPACE,
    UNODE_TYPE_MODULE,
    UNODE_TYPE_FUNCTION,
    UNODE_TYPE_SCOPE,
} unode_type_t;

typedef struct
{
    unode_type_t type;
    char* name;
    utoken_t* token;

    union
    {
    };
} unode_t;

typedef

typedef enum
{
    UOP_CODE_MATH_ADD, 
    UOP_CODE_MATH_SUB, 
    UOP_CODE_MATH_MULT,
    UOP_CODE_MATH_DIV,
    UOP_CODE_MATH_MOD,
    UOP_CODE_MATH_NEG,

    UOP_CODE_LOGIC_AND,
    UOP_CODE_LOGIC_OR,
    UOP_CODE_LOGIC_XOR,
    UOP_CODE_LOGIC_NOT,

} uopcode_t;
