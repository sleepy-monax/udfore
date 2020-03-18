#include <string.h>

#include "udfore/token/Token.h"

TokenLiteralToType operator_tokens[] = {
    {"=", TOKEN_EQUAL},
    {"!=", TOKEN_NOTEQUAL},
    {">", TOKEN_BIGGER_THAN},
    {"<", TOKEN_LESS_THAN},
    {">=", TOKEN_BIGGER_OR_EQUAL_THAN},
    {"<=", TOKEN_LESS_OR_EQUAL_THAN},
    
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
    {"->", TOKEN_ARROW},

    {"(", TOKEN_LPARENT},
    {")", TOKEN_RPARENT},
    {"{", TOKEN_LBRACE},
    {"}", TOKEN_RBRACE},
    {"[", TOKEN_LBRACKET},
    {"]", TOKEN_RBRACKET},
    {",", TOKEN_COMMA},
    {";", TOKEN_SEMICOLON},

    {"?", TOKEN_QUESTION},
    {":", TOKEN_COLON},
    {NULL, -1},
};

bool token_literal_is_operator(const char *literal)
{
    for (size_t i = 0; operator_tokens[i].literal != NULL; i++)
    {
        if (strcmp(operator_tokens[i].literal, literal) == 0)
        {
            return true;
        }
    }

    return false;
}

TokenType operator_literal_to_token_type(const char *literal)
{
    for (size_t i = 0; operator_tokens[i].literal != NULL; i++)
    {
        if (strcmp(operator_tokens[i].literal, literal) == 0)
        {
            return operator_tokens[i].type;
        }
    }

    return TOKEN_ILLEGAL;
}

const char *operator_token_type_to_literal(TokenType type)
{
    for (size_t i = 0; operator_tokens[i].literal != NULL; i++)
    {
        if (operator_tokens[i].type == type)
        {
            return operator_tokens[i].literal;
        }
    }

    return "ILLEGAL";
}
