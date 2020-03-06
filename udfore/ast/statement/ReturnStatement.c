#include "udfore/ast/Statement.h"

void returnstatement_destroy(ASTReturnStatement *statement)
{
    astnode_destroy(ASTNODE(statement->expression));

    free(statement);
}

void returnstatement_serialize(ASTReturnStatement *statement, Buffer *buffer)
{
    buffer_append_str(buffer, "return ");
    astnode_serialize_continue(ASTNODE(statement->expression), buffer);
}

ASTStatement *returnstatement_create(ASTExpression *expression)
{
    ASTReturnStatement *statement = __create(ASTReturnStatement);

    statement->expression = expression;

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)returnstatement_destroy;
    ASTNODE(statement)->serialize = (ASTNodeSerializeCallback)returnstatement_serialize;

    return (ASTStatement *)statement;
}