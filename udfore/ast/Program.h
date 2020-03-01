#pragma once

#include "udfore/ast/Node.h"
#include "udfore/utils/List.h"

struct ASTStatement;

typedef struct
{
    ASTNode node;

    List *statements;
} ASTProgram;

ASTProgram *astprogram_create(void);

void astprogram_append_statement(ASTProgram *program, struct ASTStatement *statement);
