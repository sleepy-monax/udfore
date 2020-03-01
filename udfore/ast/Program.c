#include "udfore/ast/Program.h"

void astprogram_append_statement(ASTProgram *program, struct ASTStatement *statement)
{
    list_pushback(program->statements, statement);
}

void astprogram_destroy(ASTProgram *program)
{
    list_destroy_with_callback(program->statements, (ListDestroyElementCallback)astnode_destroy);
    free(program);
}

void astprogram_serialize(ASTProgram *program, Buffer *buffer)
{
    list_foreach(struct ASTStatement, statement, program->statements)
    {
        astnode_serialize_continue(ASTNODE(statement), buffer);
        buffer_append_chr(buffer, ';');
    }
}

ASTProgram *astprogram_create(void)
{
    ASTProgram *program = __create(ASTProgram);

    program->statements = list_create();

    ASTNODE(program)->destroy = (ASTNodeDestroyCallback)astprogram_destroy;
    ASTNODE(program)->serialize = (ASTNodeSerializeCallback)astprogram_serialize;

    return program;
}
