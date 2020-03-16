#include <string.h>

#include "udfore/ast/Expression.h"
#include "udfore/ast/Statement.h"
#include "udfore/parser/Parser.h"
#include "udfore/token/Token.h"
#include "udfore/utils/Logger.h"

Parser *parser_create(Lexer *lexer)
{
    Parser *parser = __create(Parser);

    parser->lexer = lexer;

    parser_advance(parser);
    parser_advance(parser);

    return parser;
}

void parser_destroy(Parser *parser)
{
    if (parser->current)
    {
        token_destroy(parser->current);
    }

    if (parser->next)
    {
        token_destroy(parser->next);
    }

    if (parser->previous)
    {
        token_destroy(parser->previous);
    }

    free(parser);
}

void parser_advance(Parser *parser)
{
    if (parser->previous)
    {
        token_destroy(parser->previous);
    }

    parser->previous = parser->current;
    parser->current = parser->next;
    parser->next = lexer_next_token(parser->lexer);
}

Token *parser_current(Parser *parser)
{
    return parser->current;
}

Token *parser_next(Parser *parser)
{
    return parser->next;
}

Token *parser_previous(Parser *parser)
{
    return parser->previous;
}

bool parser_current_is(Parser *parser, TokenType expected)
{
    return parser->current->type == expected;
}

bool parser_next_is(Parser *parser, TokenType expected)
{
    return parser->next->type == expected;
}

bool parser_expect_current(Parser *parser, TokenType *expected)
{
    Token *token = parser_current(parser);

    for (size_t i = 0; expected[i]; i++)
    {
        if (token->type == expected[i])
        {
            return true;
        }
    }

    logger_error(
        "Unexpected token %s at line %d column %d",
        token_as_string(token),
        token->location.line,
        token->location.column);

    return false;
}

bool parser_expect_next(Parser *parser, TokenType *expected)
{
    Token *token = parser_next(parser);

    for (size_t i = 0; expected[i]; i++)
    {
        if (token->type == expected[i])
        {
            return true;
        }
    }

    logger_error(
        "Unexpected token %s at line %d column %d",
        token_as_string(token),
        token->location.line,
        token->location.column);

    return false;
}
