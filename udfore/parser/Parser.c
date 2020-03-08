#include <string.h>

#include "udfore/ast/Expression.h"
#include "udfore/ast/Statement.h"
#include "udfore/parser/Parser.h"
#include "udfore/token/Token.h"
#include "udfore/utils/Logger.h"

Token *parser_current(Parser *parser) { return parser->current; }
Token *parser_next(Parser *parser) { return parser->next; }
Token *parser_previous(Parser *parser) { return parser->previous; }

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

bool parser_next_is(Parser *parser, TokenType expected)
{
    return parser->next->type == expected;
}

bool parser_current_is(Parser *parser, TokenType expected)
{
    return parser->current->type == expected;
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

ASTExpression *parser_parse_expression(Parser *parser)
{
    while (!parser_next_is(parser, TOKEN_SEMICOLON))
    {
        parser_advance(parser);
    }

    return NULL;
}

ASTStatement *parser_parse_statement(Parser *parser)
{
    switch (parser_current(parser)->type)
    {
    case TOKEN_LET:
    {
        if (!parser_expect_next(parser, (TokenType[]){TOKEN_IDENTIFIER, 0}))
        {
            return NULL;
        }

        parser_advance(parser); // skip the let keyword

        char *identifier = strdup(parser_current(parser)->chr);

        if (!parser_expect_next(parser, (TokenType[]){TOKEN_ASSIGN, 0}))
        {
            free(identifier);

            return NULL;
        }

        parser_advance(parser); // skip the identifier
        parser_advance(parser); // skip the assign operator

        return letstatement_create(identifier, parser_parse_expression(parser));
    }
    case TOKEN_RETURN:
    {
        parser_advance(parser); // skip the return keyword

        return returnstatement_create(parser_parse_expression(parser));
    }
    case TOKEN_LBRACE:
    {
        parser_advance(parser); //skip the lbrace

        ASTBlockStatement *block_statement = blockstatement_create();

        while (!parser_current_is(parser, TOKEN_RBRACE) && !parser_current_is(parser, TOKEN_EOF))
        {
            ASTStatement *inner_statement = parser_parse_statement(parser);

            if (inner_statement)
            {
                blockstatement_appent_statement(block_statement, inner_statement);
            }

            parser_advance(parser);
        }

        return ASTSTATEMENT(block_statement);
    }
    default:
        return NULL;
    }
}

ASTProgram *parser_parse(Parser *parser)
{
    ASTProgram *program = astprogram_create();

    while (!parser_current_is(parser, TOKEN_EOF))
    {
        ASTStatement *statement = parser_parse_statement(parser);

        if (statement)
        {
            astprogram_append_statement(program, statement);
        }

        parser_advance(parser); // skip rbrace
    }

    return program;
}

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
