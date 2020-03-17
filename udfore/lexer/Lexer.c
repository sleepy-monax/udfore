#include "udfore/lexer/Lexer.h"
#include "udfore/utils/Logger.h"

Lexer *lexer_create(Source *source)
{
    Lexer *lexer = __create(Lexer);

    lexer->source = source;
    lexer->current.line = 1;
    lexer->current.column = 1;

    return lexer;
}

void lexer_destroy(Lexer *lexer)
{
    free(lexer);
}

bool lexer_is_EOF(Lexer *lexer)
{
    return source_is_EOF(lexer->source);
}

void lexer_next_char(Lexer *lexer)
{
    source_next_char(lexer->source);

    if (!source_is_EOF(lexer->source))
    {
        if (source_current_char(lexer->source) == '\n')
        {
            lexer->current.line++;
            lexer->current.column = 1;
        }
        else
        {
            lexer->current.column++;
        }
    }
}

char lexer_current_char(Lexer *lexer)
{
    return source_current_char(lexer->source);
}

char lexer_peek_char(Lexer *lexer)
{
    return source_peek_char(lexer->source);
}

void lexer_eat_white_space(Lexer *lexer)
{
    while (utils_is_white_space(lexer_current_char(lexer)))
    {
        lexer_next_char(lexer);
    }
}

bool lexer_read_number(Lexer *lexer, Token *current_token)
{
    if (!utils_is_number(lexer_current_char(lexer)))
    {
        return false;
    }

    while (utils_is_number(lexer_peek_char(lexer)))
    {
        lexer_next_char(lexer);
        token_append(current_token, lexer_current_char(lexer));
    }

    current_token->type = TOKEN_NUMBER;

    return true;
}

bool lexer_read_string(Lexer *lexer, Token *current_token)
{
    if (!(lexer_current_char(lexer) == '"'))
    {
        return false;
    }

    // Trim the " a the start of the token
    current_token->lenght = 0;

    while (lexer_peek_char(lexer) != '"' && !lexer_is_EOF(lexer))
    {
        lexer_next_char(lexer);
        token_append(current_token, lexer_current_char(lexer));
    }

    // Skip the last "
    if (lexer_peek_char(lexer) == '"')
    {
        lexer_next_char(lexer);
    }

    current_token->type = TOKEN_STRING;

    return true;
}

bool lexer_read_operator(Lexer *lexer, Token *current_token)
{
    char literal1[] = {
        lexer_current_char(lexer),
        '\0',
    };

    char literal2[] = {
        lexer_current_char(lexer),
        lexer_peek_char(lexer),
        '\0',
    };

    if (token_literal_is_operator(literal2))
    {
        lexer_next_char(lexer);
        token_append(current_token, lexer_current_char(lexer));

        current_token->type = operator_literal_to_token_type(literal2);

        return true;
    }

    if (token_literal_is_operator(literal1))
    {
        current_token->type = operator_literal_to_token_type(literal1);

        return true;
    }

    return false;
}

bool lexer_read_identifier_or_keyword(Lexer *lexer, Token *current_token)
{
    if (!utils_is_identifier(lexer_current_char(lexer)))
    {
        return false;
    }

    while (utils_is_identifier(lexer_peek_char(lexer)) ||
           utils_is_number(lexer_peek_char(lexer)))
    {
        lexer_next_char(lexer);
        token_append(current_token, lexer_current_char(lexer));
    }

    current_token->type = TOKEN_IDENTIFIER;

    if (token_literal_is_keyword(current_token->chr))
    {
        current_token->type = keyword_literal_to_token_type(current_token->chr);
    }

    return true;
}

Token *lexer_next_token(Lexer *lexer)
{
    lexer_eat_white_space(lexer);

    Token *tok = token_create(TOKEN_ILLEGAL, lexer->current, lexer_current_char(lexer));

    if (!(lexer_read_operator(lexer, tok) ||
          lexer_read_number(lexer, tok) ||
          lexer_read_string(lexer, tok) ||
          lexer_read_identifier_or_keyword(lexer, tok)))
    {
        if (lexer_is_EOF(lexer))
        {
            tok->type = TOKEN_EOF;
        }
        else
        {
            logger_warn("lexer_next_token got an illegale token: ln%d, col%d \"%s\"", tok->location.line, tok->location.column, tok->chr);
        }
    }

    lexer_next_char(lexer);
    // logger_trace("lexer_next_token return ln%d, col%d %s: \"%s\"", tok->location.line, tok->location.column, token_as_string(tok), tok->chr);

    return tok;
}