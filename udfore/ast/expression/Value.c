#include "udfore/ast/Expression.h"

void expression_value_destroy(ASTValueExpression *expression)
{
    free(expression);
}

void expression_value_serialize(ASTValueExpression *expression, Buffer *buffer)
{
    value_serialize(expression->value, buffer);
}

ASTValueExpression *expression_value_create(Value value)
{
    ASTValueExpression *expression = __create(ASTValueExpression);

    ASTNODE(expression)->destroy = (ASTNodeDestroyCallback)expression_value_destroy;
    ASTNODE(expression)->serialize = (ASTNodeSerializeCallback)expression_value_serialize;

    expression->value = value;

    return expression;
}