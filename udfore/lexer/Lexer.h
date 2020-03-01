#pragma once

#include "udfore/source/Source.h"
#include "udfore/source/SourceLocation.h"
#include "udfore/token/Token.h"

typedef struct
{
    Source *source;

    SourceLocation current;
} Lexer;

Lexer *lexer_create(Source *source);

void lexer_destroy(Lexer *lexer);

bool lexer_is_EOF(Lexer *lexer);

Token *lexer_next_token(Lexer *lexer);
