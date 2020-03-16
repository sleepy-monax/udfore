#pragma once

#include "udfore/ast/Expression.h"
#include "udfore/ast/Node.h"
#include "udfore/utils/List.h"

typedef struct ASTStatement
{
    ASTNode node;
} ASTStatement;

#define ASTSTATEMENT(__subclass) ((ASTStatement *)(__subclass))

typedef struct
{
    ASTStatement statement;

    char *identifier;
    ASTExpression *expression;
} ASTLetStatement;

ASTLetStatement *letstatement_create(char *identifier, ASTExpression *expression);

typedef struct
{
    ASTStatement statement;

    ASTExpression *expression;
} ASTReturnStatement;

ASTReturnStatement *returnstatement_create(ASTExpression *expression);

typedef struct
{
    ASTStatement statement;

    List *statements;
} ASTBlockStatement;

ASTBlockStatement *blockstatement_create(void);

void blockstatement_appent_statement(ASTBlockStatement *blockstatement, ASTStatement *statement);

typedef struct
{
    ASTStatement statement;

    ASTExpression *expression;
} ASTExpressionStatement;

ASTExpressionStatement *expressionstatement_create(ASTExpression *expression);
