#include "udfore/parser/Parser.h"

ASTExpression *parser_parse_expression(Parser *parser)
{

    while (!parser_next_is(parser, TOKEN_SEMICOLON) && !parser_next_is(parser, TOKEN_EOF) && !parser_next_is(parser, TOKEN_RBRACE))
    {
        parser_advance(parser);
    }

    return NULL;
}