#pragma once

#include "udfore/ast/Expression.h"
#include "udfore/ast/Program.h"
#include "udfore/ast/Statement.h"
#include "udfore/lexer/Lexer.h"
#include "udfore/parser/Expression.h"

typedef struct Parser
{
    Lexer *lexer;

    Token *current;
    Token *next;
    Token *previous;
} Parser;

Parser *parser_create(Lexer *lexer);

void parser_destroy(Parser *parser);

void parser_advance(Parser *parser);

//

Token *parser_previous(Parser *parser);

Token *parser_current(Parser *parser);

Token *parser_next(Parser *parser);

//

bool parser_current_is(Parser *parser, TokenType expected);

bool parser_next_is(Parser *parser, TokenType expected);

//

bool parser_expect_current(Parser *parser, TokenType *expected);

bool parser_expect_next(Parser *parser, TokenType *expected);

//

ASTProgram *parser_parse_program(Parser *parser);

ASTStatement *parser_parse_statement(Parser *parser);

ASTExpression *parser_parse_expression(Parser *parser);

ASTExpression *parser_parse_expression_with_precedence(Parser *parser, ExpressionPrecedence precedence);
