#pragma once

typedef enum
{
    AST_NODE_PROGRAM,

    __AST_NODE_TYPE_COUNT
} ASTNodeType;

typedef struct
{
    ASTNodeType type;
} ASTNode;
