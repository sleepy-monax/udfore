#pragma once

#include "udfore/ast/Node.h"

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
