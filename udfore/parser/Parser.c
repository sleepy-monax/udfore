#include "udfore/parser/Parser.h"
#include "udfore/ast/Expression.h"
#include "udfore/ast/Statement.h"
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

bool parser_expect(Parser *parser, TokenType expected)
{
    Token *token = parser_next(parser);

    if (token->type == expected)
    {
        return true;
    }

    logger_error(
        "Unexpected token, expected %s but got %s at line %d column %d",
        token_type_as_string(expected),
        token_as_string(token),
        token->line,
        token->column);

    return false;
}

ASTExpression *parser_parse_expression(Parser *parser)
{
    (void)parser;

    return NULL;
}

ASTStatement *parser_parse_statement(Parser *parser)
{
    (void)parser;

    return NULL;
}

ASTProgram *parser_parse(Parser *parser)
{
    ASTProgram *program = astprogram_create();

    while (!lexer_is_EOF(parser->lexer))
    {
        ASTStatement *statement = parser_parse_statement(parser);

        if (statement)
        {
            astprogram_append_statement(program, statement);
        }

        parser_advance(parser);
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
