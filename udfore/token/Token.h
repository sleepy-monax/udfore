#pragma once

#include "udfore/source/SourceLocation.h"
#include "udfore/utils/Utils.h"

#define TOKEN_TYPES_LIST(__ENTRY)       \
    __ENTRY(TOKEN_ILLEGAL)              \
                                        \
    /* Operators */                     \
    __ENTRY(TOKEN_EQUAL)                \
    __ENTRY(TOKEN_NOTEQUAL)             \
    __ENTRY(TOKEN_BIGGER_THAN)          \
    __ENTRY(TOKEN_LESS_THAN)            \
    __ENTRY(TOKEN_BIGGER_OR_EQUAL_THAN) \
    __ENTRY(TOKEN_LESS_OR_EQUAL_THAN)   \
    __ENTRY(TOKEN_ASSIGN)               \
    __ENTRY(TOKEN_PLUS)                 \
    __ENTRY(TOKEN_PLUSPLUS)             \
    __ENTRY(TOKEN_MINUS)                \
    __ENTRY(TOKEN_MINUSMINUS)           \
    __ENTRY(TOKEN_MOD)                  \
    __ENTRY(TOKEN_MULT)                 \
    __ENTRY(TOKEN_DIV)                  \
                                        \
    __ENTRY(TOKEN_DOT)                  \
    __ENTRY(TOKEN_DOTDOT)               \
    __ENTRY(TOKEN_ARROW)                \
                                        \
    /* Literals */                      \
    __ENTRY(TOKEN_NUMBER)               \
    __ENTRY(TOKEN_STRING)               \
    __ENTRY(TOKEN_IDENTIFIER)           \
                                        \
    /* Separators */                    \
    __ENTRY(TOKEN_LPARENT)              \
    __ENTRY(TOKEN_RPARENT)              \
    __ENTRY(TOKEN_LBRACE)               \
    __ENTRY(TOKEN_RBRACE)               \
    __ENTRY(TOKEN_LBRACKET)             \
    __ENTRY(TOKEN_RBRACKET)             \
    __ENTRY(TOKEN_COMMA)                \
    __ENTRY(TOKEN_SEMICOLON)            \
    __ENTRY(TOKEN_QUESTION)             \
    __ENTRY(TOKEN_COLON)                \
                                        \
    /* Keywords */                      \
    __ENTRY(TOKEN_CAST)                 \
    __ENTRY(TOKEN_CONSTRUCTOR)          \
    __ENTRY(TOKEN_DESTRUCTOR)           \
    __ENTRY(TOKEN_FROM)                 \
    __ENTRY(TOKEN_FUNCTION)             \
    __ENTRY(TOKEN_LET)                  \
    __ENTRY(TOKEN_MODULE)               \
    __ENTRY(TOKEN_RETURN)               \
    __ENTRY(TOKEN_SPEC)                 \
    __ENTRY(TOKEN_TAKE)                 \
    __ENTRY(TOKEN_TYPE)                 \
    __ENTRY(TOKEN_USE)                  \
                                        \
    __ENTRY(TOKEN_EOF)

#define TOKEN_TYPE_ENUM_ENTRY(__entry) __entry,
typedef enum
{
    TOKEN_TYPES_LIST(TOKEN_TYPE_ENUM_ENTRY)
        __TOKEN_TYPE_COUNT,
} TokenType;
#undef TOKEN_TYPE_ENUM_ENTRY

typedef struct
{
    TokenType type;

    SourceLocation location;

    int lenght;
    char *chr;
} Token;

typedef struct
{
    const char *literal;
    TokenType type;
} TokenLiteralToType;

Token *token_create(TokenType type, SourceLocation location, char c);

void token_destroy(Token *token);

Token *token_append(Token *token, char c);

const char *token_as_string(Token *token);

const char *token_type_as_string(TokenType type);

bool token_literal_is_keyword(const char *literal);

bool token_literal_is_operator(const char *literal);

TokenType keyword_literal_to_token_type(const char *literal);

TokenType operator_literal_to_token_type(const char *literal);

const char *operator_token_type_to_literal(TokenType type);
