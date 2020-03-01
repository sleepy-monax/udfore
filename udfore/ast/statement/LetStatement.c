#include "udfore/ast/Statement.h"

void letstatement_destroy(ASTLetStatement *statement)
{
    if (statement->identifier)
    {
        free(statement->identifier);
    }

    astnode_destroy(ASTNODE(statement->expression));
}

ASTStatement *letstatement_create(char *identifier, ASTExpression *expression)
{
    ASTLetStatement *statement = __create(ASTLetStatement);

    statement->identifier = identifier;
    statement->expression = expression;

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)letstatement_destroy;

    return (ASTStatement *)statement;
}