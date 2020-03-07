#include "udfore/ast/Statement.h"

void blockstatement_destroy(ASTBlockStatement *statement)
{
    list_destroy_with_callback(statement->statements, (ListDestroyElementCallback)astnode_destroy);
    free(statement);
}

void blockstatement_serialize(ASTBlockStatement *statement, Buffer *buffer)
{
    buffer_append_str(buffer, "{");

    list_foreach(struct ASTStatement, statement, statement->statements)
    {
        astnode_serialize_continue(ASTNODE(statement), buffer);
        buffer_append_str(buffer, "; ");
    }

    buffer_append_str(buffer, "}");
}

void blockstatement_appent_statement(ASTBlockStatement *block_statement, ASTStatement *statement)
{
    list_pushback(block_statement->statements, statement);
}

ASTBlockStatement *blockstatement_create(void)
{
    ASTBlockStatement *statement = __create(ASTBlockStatement);

    statement->statements = list_create();

    ASTNODE(statement)->destroy = (ASTNodeDestroyCallback)blockstatement_destroy;
    ASTNODE(statement)->serialize = (ASTNodeSerializeCallback)blockstatement_serialize;

    return statement;
}
