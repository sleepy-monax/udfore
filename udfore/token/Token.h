#pragma once

#include "udfore/utils/Utils.h"

#define TOKEN_TYPES_LIST(__ENTRY) \
    __ENTRY(TOKEN_ILLEGAL)        \
                                  \
    /* Operators */               \
    __ENTRY(TOKEN_EQUAL)          \
    __ENTRY(TOKEN_NOTEQUAL)       \
    __ENTRY(TOKEN_ASSIGN)         \
    __ENTRY(TOKEN_PLUS)           \
    __ENTRY(TOKEN_PLUSPLUS)       \
    __ENTRY(TOKEN_MINUS)          \
    __ENTRY(TOKEN_MINUSMINUS)     \
    __ENTRY(TOKEN_MOD)            \
    __ENTRY(TOKEN_MULT)           \
    __ENTRY(TOKEN_DIV)            \
                                  \
    __ENTRY(TOKEN_DOT)            \
    __ENTRY(TOKEN_DOTDOT)         \
                                  \
    /* Literals */                \
    __ENTRY(TOKEN_NUMBER)         \
    __ENTRY(TOKEN_STRING)         \
    __ENTRY(TOKEN_IDENTIFIER)     \
                                  \
    /* Separators */              \
    __ENTRY(TOKEN_LPARENT)        \
    __ENTRY(TOKEN_RPARENT)        \
    __ENTRY(TOKEN_LBRACE)         \
    __ENTRY(TOKEN_RBRACE)         \
    __ENTRY(TOKEN_LBRACKET)       \
    __ENTRY(TOKEN_RBRACKET)       \
    __ENTRY(TOKEN_COMMA)          \
    __ENTRY(TOKEN_SEMICOLON)      \
                                  \
    /* Keywords */                \
    __ENTRY(TOKEN_USE)            \
    __ENTRY(TOKEN_MODULE)         \
    __ENTRY(TOKEN_FUNCTION)       \
                                  \
    __ENTRY(TOKEN_EOF)

typedef enum
{
#define TOKEN_TYPE_ENUM_ENTRY(__entry) __entry,
    TOKEN_TYPES_LIST(TOKEN_TYPE_ENUM_ENTRY)
        __TOKEN_TYPE_COUNT,
} TokenType;

typedef struct
{
    TokenType type;

    int line;
    int column;

    int lenght;
    char *chr;
} Token;

Token *token_create(TokenType type, int line, int column, char c);

void token_destroy(Token *token);

Token *token_append(Token *token, char c);

const char *token_as_string(Token *token);

const char *token_type_as_string(TokenType type);
