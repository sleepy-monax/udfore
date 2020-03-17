#include "udfore/ast/Expression.h"
#include <string.h>

void expression_identifier_destroy(ASTExpressionIdentifier *expression)
{
    if (expression->name)
    {
        free(expression->name);
    }

    free(expression);
}

void expression_identifier_serialize(ASTExpressionIdentifier *expression, Buffer *buffer)
{
    buffer_append_str(buffer, expression->name);
}

ASTExpressionIdentifier *expression_identifier_create(const char *name)
{
    ASTExpressionIdentifier *expression = __create(ASTExpressionIdentifier);

    ASTNODE(expression)->destroy = (ASTNodeDestroyCallback)expression_identifier_destroy;
    ASTNODE(expression)->serialize = (ASTNodeSerializeCallback)expression_identifier_serialize;

    expression->name = strdup(name);

    return expression;
}