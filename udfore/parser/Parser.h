#pragma once

#include "udfore/ast/Program.h"
#include "udfore/lexer/Lexer.h"

typedef struct
{
    Lexer *lexer;

    Token *current;
    Token *next;
    Token *previous;
} Parser;

Parser *parser_create(Lexer *lexer);

void parser_destroy(Parser *parser);

ASTProgram *parser_parse(Parser *parser);
