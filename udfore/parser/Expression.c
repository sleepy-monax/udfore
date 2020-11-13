#include <inttypes.h>

#include "udfore/parser/Expression.h"
#include "udfore/parser/Parser.h"

ASTExpressionIdentifier *parser_parse_identifier(Parser *parser)
{
    return expression_identifier_create(parser_current(parser)->chr);
}

ASTValueExpression *parser_parse_value_expression(Parser *parser)
{
    int32_t s32 = 0;

    sscanf(parser_current(parser)->chr, "%" SCNd32, &s32);

    return expression_value_create(value_create_s32(s32));
}

ASTInfixExpression *parser_parse_infix_operator(Parser *parser, ASTExpression *lhs)
{
    TokenType op = parser_current(parser)->type;

    parser_advance(parser);

    return expression_infix_operator_create(op, lhs, parser_parse_expression_with_precedence(parser, parser_get_precedence(op)));
}

static ExpressionParserCallback expression_parser_callback[] = {
    {TOKEN_IDENTIFIER, PRECEDENCE_LOWEST, {.prefix = (ParserPrefixCallback)parser_parse_identifier}},
    {TOKEN_NUMBER, PRECEDENCE_LOWEST, {.prefix = (ParserPrefixCallback)parser_parse_value_expression}},

    {TOKEN_EQUAL, PRECEDENCE_EQUALS, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_NOTEQUAL, PRECEDENCE_EQUALS, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_BIGGER_THAN, PRECEDENCE_LESSGREATER, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_LESS_THAN, PRECEDENCE_LESSGREATER, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_BIGGER_OR_EQUAL_THAN, PRECEDENCE_LESSGREATER, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_LESS_OR_EQUAL_THAN, PRECEDENCE_LESSGREATER, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},

    {TOKEN_PLUS, PRECEDENCE_SUM, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_MINUS, PRECEDENCE_SUM, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_MULT, PRECEDENCE_PRODUCT, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_DIV, PRECEDENCE_PRODUCT, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},
    {TOKEN_MOD, PRECEDENCE_MOD, {.infix = (ParserInfixCallback)parser_parse_infix_operator}},

    {TOKEN_ILLEGAL, -1, {NULL, NULL, NULL}},
};

ParserPrefixCallback parser_get_prefix_callback(TokenType type)
{
    for (size_t i = 0; expression_parser_callback[i].token != TOKEN_ILLEGAL; i++)
    {
        if (expression_parser_callback[i].token == type &&
            expression_parser_callback[i].prefix != NULL)
        {
            return expression_parser_callback[i].prefix;
        }
    }

    return NULL;
}

ParserInfixCallback parser_get_infix_callback(TokenType type)
{
    for (size_t i = 0; expression_parser_callback[i].token != TOKEN_ILLEGAL; i++)
    {
        if (expression_parser_callback[i].token == type &&
            expression_parser_callback[i].infix != NULL)
        {
            return expression_parser_callback[i].infix;
        }
    }

    return NULL;
}

ParserPostfixCallback parser_get_postfix_callback(TokenType type)
{
    for (size_t i = 0; expression_parser_callback[i].token != TOKEN_ILLEGAL; i++)
    {
        if (expression_parser_callback[i].token == type &&
            expression_parser_callback[i].postfix != NULL)
        {
            return expression_parser_callback[i].postfix;
        }
    }

    return NULL;
}

ExpressionPrecedence parser_get_precedence(TokenType type)
{
    for (size_t i = 0; expression_parser_callback[i].token != TOKEN_ILLEGAL; i++)
    {
        if (expression_parser_callback[i].token == type)
        {
            return expression_parser_callback[i].precedence;
        }
    }

    return PRECEDENCE_LOWEST;
}

ExpressionPrecedence parser_next_precedence(Parser *parser)
{
    return parser_get_precedence(parser_next(parser)->type);
}

ASTExpression *parser_parse_expression(Parser *parser)
{
    return parser_parse_expression_with_precedence(parser, PRECEDENCE_LOWEST);
}

ASTExpression *parser_parse_expression_with_precedence(Parser *parser, ExpressionPrecedence precedence)
{
    ParserPrefixCallback prefix = parser_get_prefix_callback(parser_current(parser)->type);

    if (!prefix)
    {
        return NULL;
    }

    ASTExpression *lhs = prefix(parser);

    while (!parser_next_is(parser, TOKEN_SEMICOLON) &&
           precedence < parser_next_precedence(parser))
    {
        ParserInfixCallback infix = parser_get_infix_callback(parser_next(parser)->type);

        if (infix)
        {
            parser_advance(parser);
            lhs = infix(parser, lhs);
        }
        else
        {
            return lhs;
        }
    }

    return lhs;
}
