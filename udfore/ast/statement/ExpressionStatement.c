#include "udfore/ast/Statement.h"

void expressionstatement_destroy(ASTExpressionStatement *statement)
{
    astnode_destroy(ASTNODE(statement->expression));
    free(statement);
}

void expressionstatement_serialize(ASTExpressionStatement *statement, Buffer *buffer)
{
    buffer_append_str(buffer, "(expression ");
    astnode_serialize_continue(ASTNODE(statement->expression), buffer);
    buffer_append_str(buffer, ")");
}

ASTExpressionStatement *expressionstatement_create(ASTExpression *expression)
{
    ASTExpressionStatement *statement = __create(ASTExpressionStatement);

    statement->expression = expression;

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)expressionstatement_destroy;
    ASTNODE(statement)->serialize = (ASTNodeSerializeCallback)expressionstatement_serialize;

    return statement;
}
