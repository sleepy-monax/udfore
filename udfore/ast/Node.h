#pragma once

#include "udfore/source/SourceLocation.h"
#include "udfore/utils/Buffer.h"

struct ASTNode;

typedef void (*ASTNodeDestroyCallback)(struct ASTNode *node);
typedef void (*ASTNodeSerializeCallback)(struct ASTNode *node, Buffer *buffer);

typedef struct ASTNode
{
    SourceLocation location;

    ASTNodeDestroyCallback destroy;
    ASTNodeSerializeCallback serialize;
} ASTNode;

#define ASTNODE(__subclass) ((ASTNode *)(__subclass))

void astnode_destroy(ASTNode *node);

char *astnode_serialize(ASTNode *node);

void astnode_serialize_continue(ASTNode *node, Buffer *buffer);
