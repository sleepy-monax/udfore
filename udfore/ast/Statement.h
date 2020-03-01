#pragma once

#include "udfore/ast/Expression.h"
#include "udfore/ast/Node.h"
#include "udfore/utils/List.h"

typedef struct ASTStatement
{
    ASTNode node;
} ASTStatement;

typedef struct
{
    ASTStatement statement;

    char *identifier;
    ASTExpression *expression;
} ASTLetStatement;

ASTStatement *letstatement_create(char *identifier, ASTExpression *expression);

typedef struct
{
    ASTStatement statement;

    ASTExpression *expression;
} ASTReturnStatement;

ASTStatement *returnstatement_create(ASTExpression *expression);

typedef struct
{
    ASTStatement statement;

    List *statements;
} ASTBlockStatement;

typedef struct
{
    ASTStatement statement;

    ASTExpression *expression;
} ASTExpressionStatement;
