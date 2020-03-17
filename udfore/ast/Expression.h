#pragma once

#include "udfore/ast/Node.h"
#include "udfore/token/Token.h"

typedef struct ASTExpression
{
    ASTNode node;
} ASTExpression;

typedef struct
{
    ASTExpression expression;

    char *name;
} ASTExpressionIdentifier;

ASTExpressionIdentifier *expression_identifier_create(const char *name);

typedef struct
{
    ASTExpression expression;

    TokenType operator;
    ASTExpression *lhs;
    ASTExpression *rhs;
} ASTInfixExpression;

ASTInfixExpression *expression_infix_operator_create(TokenType operator, ASTExpression *lhs, ASTExpression *rhs);