#include <string.h>

#include "udfore/parser/Parser.h"

ASTLetStatement *parser_parse_letstatement(Parser *parser)
{
    if (!parser_expect_current(parser, (TokenType[]){TOKEN_LET, 0}))
    {
        return NULL;
    }

    parser_advance(parser); // skip the let keyword

    if (!parser_expect_current(parser, (TokenType[]){TOKEN_IDENTIFIER, 0}))
    {
        return NULL;
    }

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

ASTReturnStatement *parser_parse_returnstatement(Parser *parser)
{
    if (!parser_expect_current(parser, (TokenType[]){TOKEN_RETURN, 0}))
    {
        return NULL;
    }

    parser_advance(parser); // skip the return keyword

    return returnstatement_create(parser_parse_expression(parser));
}

ASTBlockStatement *parser_parse_blockstatement(Parser *parser)
{
    if (!parser_expect_current(parser, (TokenType[]){TOKEN_LBRACE, 0}))
    {
        return NULL;
    }

    parser_advance(parser); //skip the lbrace

    ASTBlockStatement *block_statement = blockstatement_create();

    while (!parser_current_is(parser, TOKEN_RBRACE) && !parser_current_is(parser, TOKEN_EOF))
    {
        ASTStatement *inner_statement = parser_parse_statement(parser);

        if (inner_statement)
        {
            blockstatement_appent_statement(block_statement, inner_statement);
        }
    }

    return block_statement;
}

ASTExpressionStatement *parser_parse_expressionstatement(Parser *parser)
{
    return expressionstatement_create(parser_parse_expression(parser));
}

ASTStatement *parser_parse_statement(Parser *parser)
{
    ASTStatement *statement = NULL;

    switch (parser_current(parser)->type)
    {
    case TOKEN_LET:
        statement = (ASTStatement *)parser_parse_letstatement(parser);
        break;

    case TOKEN_RETURN:
        statement = (ASTStatement *)parser_parse_returnstatement(parser);
        break;

    case TOKEN_LBRACE:
        statement = (ASTStatement *)parser_parse_blockstatement(parser);
        break;

    default:
        statement = (ASTStatement *)parser_parse_expressionstatement(parser);
        break;
    }

    if (parser_current_is(parser, TOKEN_SEMICOLON))
    {
        parser_advance(parser); // skip the semi colon
    }

    return statement;
}
