#include "udfore/ast/Statement.h"

void returnstatement_destroy(ASTReturnStatement *statement)
{
    astnode_destroy(ASTNODE(statement->expression));
}

ASTStatement *returnstatement_create(ASTExpression *expression)
{
    ASTReturnStatement *statement = __create(ASTReturnStatement);

    statement->expression = expression;

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)returnstatement_destroy;

    return (ASTStatement *)statement;
}