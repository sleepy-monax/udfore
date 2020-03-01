#pragma once

#include "udfore/ast/Node.h"

typedef struct ASTStatement
{
    ASTNode node;
} ASTStatement;

typedef struct
{
    ASTStatement statement;
} ASTLetStatement;

typedef struct
{
    ASTStatement statement;
} ASTReturnStatement;
