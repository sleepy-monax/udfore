#include <string.h>

#include "udfore/token/Token.h"

TokenLiteralToType keyword_tokens[] = {
    {"cast", TOKEN_CAST},
    {"constructor", TOKEN_CONSTRUCTOR},
    {"destructor", TOKEN_DESTRUCTOR},
    {"from", TOKEN_FROM},
    {"function", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {"module", TOKEN_MODULE},
    {"return", TOKEN_RETURN},
    {"spec", TOKEN_SPEC},
    {"take", TOKEN_TAKE},
    {"type", TOKEN_TYPE},
    {"use", TOKEN_USE},
    {NULL, -1},
};

bool token_literal_is_keyword(const char *literal)
{
    for (size_t i = 0; keyword_tokens[i].literal != NULL; i++)
    {
        if (strcmp(keyword_tokens[i].literal, literal) == 0)
        {
            return true;
        }
    }

    return false;
}

TokenType keyword_literal_to_token_type(const char *literal)
{
    for (size_t i = 0; keyword_tokens[i].literal != NULL; i++)
    {
        if (strcmp(keyword_tokens[i].literal, literal) == 0)
        {
            return keyword_tokens[i].type;
        }
    }

    return TOKEN_ILLEGAL;
}
