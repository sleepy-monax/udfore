#include "udfore/ast/Expression.h"

void expression_infix_operator_destroy(ASTInfixExpression *expression)
{
    astnode_destroy(ASTNODE(expression->lhs));
    astnode_destroy(ASTNODE(expression->rhs));

    free(expression);
}

void expression_infix_operator_serialize(ASTInfixExpression *expression, Buffer *buffer)
{
    buffer_append_str(buffer, "(");
    astnode_serialize_continue(ASTNODE(expression->lhs), buffer);
    buffer_append_str(buffer, " ");
    buffer_append_str(buffer, token_type_as_string(expression->operator));
    buffer_append_str(buffer, " ");
    astnode_serialize_continue(ASTNODE(expression->rhs), buffer);
    buffer_append_str(buffer, ")");
}

ASTInfixExpression *expression_infix_operator_create(TokenType operator, ASTExpression *lhs, ASTExpression *rhs)
{
    ASTInfixExpression *expression = __create(ASTInfixExpression);

    ASTNODE(expression)->destroy = (ASTNodeDestroyCallback)expression_infix_operator_destroy;
    ASTNODE(expression)->serialize = (ASTNodeSerializeCallback)expression_infix_operator_serialize;

    expression->operator= operator;
    expression->lhs = lhs;
    expression->rhs = rhs;

    return expression;
}
