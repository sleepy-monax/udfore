#include "udfore/parser/Expression.h"
#include "udfore/parser/Parser.h"

ASTExpressionIdentifier *parser_parse_identifier(Parser *parser)
{
    return expression_identifier_create(parser_current(parser)->chr);
}

static ExpressionParserCallback expression_parser_callback[] = {
    {TOKEN_IDENTIFIER, PRECEDENCE_LOWEST, (ParserPrefixCallback)parser_parse_identifier, NULL, NULL},
    {TOKEN_ILLEGAL, -1, NULL, NULL, NULL},
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

ASTExpression *parser_parse_expression(Parser *parser)
{
    ParserPrefixCallback prefix = parser_get_prefix_callback(parser_current(parser)->type);

    if (prefix)
    {
        return prefix(parser);
    }

    while (!parser_next_is(parser, TOKEN_SEMICOLON) && !parser_next_is(parser, TOKEN_EOF))
    {
        parser_advance(parser);
    }

    /*
	postfix := p.postfixParseFns[p.curToken.Type]
	if postfix != nil {
		return (postfix())
	}
	prefix := p.prefixParseFns[p.curToken.Type]
	if prefix == nil {
		p.noPrefixParseFnError(p.curToken.Type)
		return nil
	}
	leftExp := prefix()
	for !p.peekTokenIs(token.SEMICOLON) && precedence < p.peekPrecedence() {
		infix := p.infixParseFns[p.peekToken.Type]
		if infix == nil {
			return leftExp
		}
		p.nextToken()
		leftExp = infix(leftExp)
	}
	return leftExp
*/

    return NULL;
}