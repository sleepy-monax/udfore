#include "udfore/ast/Statement.h"

void letstatement_destroy(ASTLetStatement *statement)
{
    if (statement->identifier)
    {
        free(statement->identifier);
    }

    astnode_destroy(ASTNODE(statement->expression));

    free(statement);
}

void letstatement_serialize(ASTLetStatement *statement, Buffer *buffer)
{
    buffer_append_str(buffer, "let ");
    buffer_append_str(buffer, statement->identifier);
    buffer_append_str(buffer, " := ");
    astnode_serialize_continue(ASTNODE(statement->expression), buffer);
}

ASTStatement *letstatement_create(char *identifier, ASTExpression *expression)
{
    ASTLetStatement *statement = __create(ASTLetStatement);

    statement->identifier = identifier;
    statement->expression = expression;

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)letstatement_destroy;
    ASTNODE(statement)->serialize = (ASTNodeSerializeCallback)letstatement_serialize;

    return (ASTStatement *)statement;
}