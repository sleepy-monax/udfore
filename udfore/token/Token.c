#include <assert.h>
#include <string.h>

#include "udfore/token/Token.h"
#include "udfore/utils/Utils.h"

Token *token_create(TokenType type, int line, int column, char c)
{
    Token *token = malloc(sizeof(Token));

    token->type = type;

    token->line = line;
    token->column = column;

    token->lenght = 1;

    token->chr = malloc(2);
    token->chr[0] = c;
    token->chr[1] = '\0';

    return token;
}

void token_destroy(Token *token)
{
    assert(token);
    assert(token->chr);

    free(token->chr);
    free(token);
}

static const char *token_type_string[] = {
#define TOKEN_TYPE_STRING_ENTRY(__entry) #__entry,
    TOKEN_TYPES_LIST(TOKEN_TYPE_STRING_ENTRY)};

const char *token_as_string(Token *token)
{
    assert(token);
    assert(token->type >= 0 && token->type < __TOKEN_TYPE_COUNT);

    return token_type_string[token->type];
}

const char *token_type_as_string(TokenType type)
{
    return token_type_string[type];
}

Token *token_append(Token *token, char c)
{
    token->chr = realloc(token->chr, token->lenght + 2);
    token->lenght = token->lenght + 1;
    token->chr[token->lenght - 1] = c;
    token->chr[token->lenght] = '\0';

    return token;
}
