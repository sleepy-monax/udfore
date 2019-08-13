#pragma once

#include <stdlib.h>
#include <assert.h>

#define TOKEN_TYPES_LIST(__entry) __entry(TOKEN_ILLEGAL),    \
                                                             \
                                  /* Operators */            \
                                  __entry(TOKEN_EQUAL),      \
                                  __entry(TOKEN_NOTEQUAL),   \
                                  __entry(TOKEN_ASSIGN),     \
                                  __entry(TOKEN_PLUS),       \
                                  __entry(TOKEN_PLUSPLUS),   \
                                  __entry(TOKEN_MINUS),      \
                                  __entry(TOKEN_MINUSMINUS), \
                                  __entry(TOKEN_MOD),        \
                                  __entry(TOKEN_MULT),       \
                                  __entry(TOKEN_DIV),        \
                                                             \
                                  __entry(TOKEN_DOT),        \
                                  __entry(TOKEN_DOTDOT),     \
                                                             \
                                  /* Literals */             \
                                  __entry(TOKEN_NUMBER),     \
                                  __entry(TOKEN_STRING),     \
                                  __entry(TOKEN_IDENTIFIER), \
                                                             \
                                  /* Separators */           \
                                  __entry(TOKEN_LPARENT),    \
                                  __entry(TOKEN_RPARENT),    \
                                  __entry(TOKEN_LBRACE),     \
                                  __entry(TOKEN_RBRACE),     \
                                  __entry(TOKEN_LBRACKET),   \
                                  __entry(TOKEN_RBRACKET),   \
                                  __entry(TOKEN_COMMA),      \
                                  __entry(TOKEN_SEMICOLON),  \
                                                             \
                                  /* Keywords */             \
                                  __entry(TOKEN_USE),        \
                                  __entry(TOKEN_MODULE),     \
                                  __entry(TOKEN_FUNCTION),   \
                                                             \
                                  __entry(TOKEN_EOF)

static const char *token_type_string[] = {
#define TOKEN_TYPE_STRING_ENTRY(__entry) #__entry
    TOKEN_TYPES_LIST(TOKEN_TYPE_STRING_ENTRY),
};

typedef enum
{
#define TOKEN_TYPE_ENUM_ENTRY(__entry) __entry
    TOKEN_TYPES_LIST(TOKEN_TYPE_ENUM_ENTRY),
    __TOKEN_TYPE_COUNT,
} token_type_t;

typedef struct
{
    const char *literal;
    token_type_t type;
} token_literal_to_type_t;

token_literal_to_type_t token_operators[] = {
    {"=", TOKEN_EQUAL},
    {"!=", TOKEN_NOTEQUAL},
    {":=", TOKEN_ASSIGN},
    {"+", TOKEN_PLUS},
    {"++", TOKEN_PLUSPLUS},
    {"-", TOKEN_MINUS},
    {"--", TOKEN_MINUSMINUS},
    {"*", TOKEN_MULT},
    {"%", TOKEN_MOD},
    {"/", TOKEN_DIV},

    {".", TOKEN_DOT},
    {"..", TOKEN_DOTDOT},

    {"(", TOKEN_LPARENT},
    {")", TOKEN_RPARENT},
    {"{", TOKEN_LBRACE},
    {"}", TOKEN_RBRACE},
    {"[", TOKEN_LBRACKET},
    {"]", TOKEN_RBRACKET},
    {",", TOKEN_COMMA},
    {";", TOKEN_SEMICOLON},
    {NULL, -1},
};

token_literal_to_type_t token_keywords[] = {
    {"use", TOKEN_USE},
    {"module", TOKEN_MODULE},
    {"function", TOKEN_FUNCTION},
    {NULL, -1},
};

typedef struct
{
    token_type_t type;

    int line;
    int column;

    int lenght;
    char *chr;
} token_t;

token_t *token(token_type_t type, int line, int column, char c)
{
    token_t *this = malloc(sizeof(token_t));

    this->type = type;

    this->line = line;
    this->column = column;

    this->lenght = 1;

    this->chr = malloc(2);
    this->chr[0] = c;
    this->chr[1] = '\0';

    return this;
}

void token_delete(token_t *this)
{
    assert(this);
    assert(this->chr);

    free(this->chr);
    free(this);
}

const char *token_type_as_string(token_t *this)
{
    assert(this);
    assert(this->type >= 0 && this->type < __TOKEN_TYPE_COUNT);

    return token_type_string[this->type];
}

token_t *token_append(token_t *this, char c)
{
    assert(this);

    this->chr = realloc(this->chr, this->lenght + 2);
    this->lenght = this->lenght + 1;
    this->chr[this->lenght - 1] = c;
    this->chr[this->lenght] = '\0';

    return this;
}
