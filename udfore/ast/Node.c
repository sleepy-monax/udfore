#include "udfore/ast/Node.h"

void astnode_destroy(ASTNode *node)
{
    if (node->destroy)
    {
        node->destroy(node);
    }
}

char *astnode_serialize(ASTNode *node)
{
    Buffer *buffer = buffer_create(128);

    astnode_serialize_continue(node, buffer);

    return buffer_finalize(buffer);
}

void astnode_serialize_continue(ASTNode *node, Buffer *buffer)
{
    if (node == NULL)
    {
        buffer_append_str(buffer, "<null>");
    }
    else if (!node->serialize)
    {
        buffer_append_str(buffer, "<invalide>");
    }
    else
    {
        node->serialize(node, buffer);
    }
}
