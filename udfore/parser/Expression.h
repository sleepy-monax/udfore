#pragma once

#include "udfore/token/Token.h"

struct Parser;
struct ASTExpression;

typedef struct ASTExpression *(*ParserPrefixCallback)(struct Parser *parser);
typedef struct ASTExpression *(*ParserInfixCallback)(struct Parser *parser, struct ASTExpression *lhs);
typedef struct ASTExpression *(*ParserPostfixCallback)(struct Parser *parser, struct ASTExpression *lhs);

typedef enum
{
    PRECEDENCE_LOWEST,
    PRECEDENCE_COND,        // OR or AND
    PRECEDENCE_ASSIGN,      // =
    PRECEDENCE_TERNARY,     // ? :
    PRECEDENCE_EQUALS,      // == or !=
    PRECEDENCE_LESSGREATER, // > or <
    PRECEDENCE_SUM,         // + or -
    PRECEDENCE_PRODUCT,     // * or /
    PRECEDENCE_POWER,       // **
    PRECEDENCE_MOD,         // %
    PRECEDENCE_PREFIX,      // -X or !X
    PRECEDENCE_CALL,        // myFunction(X)
    PRECEDENCE_INDEX,       // array[index], map[key]
} ExpressionPrecedence;

typedef struct
{
    TokenType token;
    ExpressionPrecedence precedence;

    struct
    {
        ParserPrefixCallback prefix;
        ParserInfixCallback infix;
        ParserPostfixCallback postfix;
    };
} ExpressionParserCallback;

ParserPrefixCallback parser_get_prefix_callback(TokenType type);

ParserInfixCallback parser_get_infix_callback(TokenType type);

ParserPostfixCallback parser_get_postfix_callback(TokenType type);

ExpressionPrecedence parser_get_precedence(TokenType type);
