#pragma once

#include "source.c"
#include "token.c"
#include "logger.c"

typedef struct
{
    source_t *source;

    int current_line;
    int current_column;
} lexer_t;

lexer_t *lexer(source_t *source)
{
    assert(source);

    lexer_t *this = malloc(sizeof(lexer_t));

    this->source = source;
    this->current_line = 1;
    this->current_column = 1;

    return this;
}

bool lexer_is_EOF(lexer_t *this)
{
    return source_is_EOF(this->source);
}

void lexer_next_char(lexer_t *this)
{
    this->source->next_char(this->source);

    if (source_current_char(this->source) == '\n')
    {
        this->current_line++;
        this->current_column = 1;
    }
    else
    {
        this->current_column++;
    }
}

char lexer_current_char(lexer_t *this)
{
    return source_current_char(this->source);
}

char lexer_peek_char(lexer_t *this)
{
    return source_peek_char(this->source);
}

void lexer_eat_white_space(lexer_t *this)
{
    while (utils_is_white_space(lexer_current_char(this)))
    {
        lexer_next_char(this);
    }
}

bool lexer_read_operator(lexer_t *this, token_t *current_token)
{
    token_literal_to_type_t *matching = NULL;

    for (size_t i = 0; token_operators[i].literal != NULL; i++)
    {
        token_literal_to_type_t *op = &token_operators[i];

        if (op->literal[0] == lexer_current_char(this))
        {
            if (op->literal[1] == '\0')
            {
                matching = op;
            }
            else if (op->literal[1] == lexer_peek_char(this))
            {
                lexer_next_char(this);
                current_token->type = op->type;
                token_append(current_token, lexer_current_char(this));

                return true;
            }
        }
    }

    if (matching != NULL)
    {
        current_token->type = matching->type;
        return true;
    }

    return false;
}

bool lexer_read_number(lexer_t *this, token_t *current_token)
{
    if (!utils_is_number(lexer_current_char(this)))
    {
        return false;
    }

    while (utils_is_number(lexer_peek_char(this)))
    {
        lexer_next_char(this);
        token_append(current_token, lexer_current_char(this));
    }

    current_token->type = TOKEN_NUMBER;

    return true;
}

bool lexer_read_string(lexer_t *this, token_t *current_token)
{
    if (!(lexer_current_char(this) == '"'))
    {
        return false;
    }

    // Trim the " a the start of the token
    current_token->lenght = 0;

    while (lexer_peek_char(this) != '"' && !lexer_is_EOF(this))
    {
        lexer_next_char(this);
        token_append(current_token, lexer_current_char(this));
    }

    // Skip the last "
    if (lexer_peek_char(this) == '"')
    {
        lexer_next_char(this);
    }

    current_token->type = TOKEN_STRING;

    return true;
}

bool lexer_read_identifier_or_keyword(lexer_t *this, token_t *current_token)
{
    if (!utils_is_letter(lexer_current_char(this)))
    {
        return false;
    }

    while (utils_is_letter(lexer_peek_char(this)))
    {
        lexer_next_char(this);
        token_append(current_token, lexer_current_char(this));
    }

    current_token->type = TOKEN_IDENTIFIER;

    for (size_t i = 0; token_keywords[i].literal != NULL; i++)
    {
        if (strcmp(token_keywords[i].literal, current_token->chr) == 0)
        {
            current_token->type = token_keywords[i].type;
        }
    }

    return true;
}

token_t *lexer_next_token(lexer_t *this)
{
    lexer_eat_white_space(this);

    token_t *tok = token(TOKEN_ILLEGAL, this->current_line, this->current_column, lexer_current_char(this));

    if (!(lexer_read_operator(this, tok) ||
          lexer_read_number(this, tok) ||
          lexer_read_string(this, tok) ||
          lexer_read_identifier_or_keyword(this, tok)))
    {
        logger_warn("lexer_next_token got an illegale token: ln%d, col%d \"%s\"", tok->line, tok->column, tok->chr);
    }

    lexer_next_char(this);
    logger_trace("lexer_next_token return ln%d, col%d %s: \"%s\"", tok->line, tok->column, token_type_as_string(tok), tok->chr);

    return tok;
}