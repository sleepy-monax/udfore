#include <string.h>

#include "udfore/lexer/Lexer.h"
#include "udfore/utils/Logger.h"

Lexer *lexer_create(Source *source)
{
    Lexer *lexer = __create(Lexer);

    lexer->source = source;
    lexer->current_line = 1;
    lexer->current_column = 1;

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

    if (source_current_char(lexer->source) == '\n')
    {
        lexer->current_line++;
        lexer->current_column = 1;
    }
    else
    {
        lexer->current_column++;
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

typedef struct
{
    const char *literal;
    TokenType type;
} token_literal_to_type_t;

token_literal_to_type_t token_operators[] = {
    {"=", TOKEN_EQUAL},
    {"!=", TOKEN_NOTEQUAL},
    {">", TOKEN_BIGGER_THAN},
    {"<", TOKEN_LESS_THAN},
    {":=", TOKEN_ASSIGN},
    {"+", TOKEN_PLUS},
    {"++", TOKEN_PLUSPLUS},
    {"-", TOKEN_MINUS},
    {"--", TOKEN_MINUSMINUS},
    {"*", TOKEN_MULT},
    {"%", TOKEN_MOD},
    {"/", TOKEN_DIV},

    {".", TOKEN_DOT},
    {"..", TOKEN_DOTDOT},
    {"->", TOKEN_ARROW},

    {"(", TOKEN_LPARENT},
    {")", TOKEN_RPARENT},
    {"{", TOKEN_LBRACE},
    {"}", TOKEN_RBRACE},
    {"[", TOKEN_LBRACKET},
    {"]", TOKEN_RBRACKET},
    {",", TOKEN_COMMA},
    {";", TOKEN_SEMICOLON},

    {"?", TOKEN_QUESTION},
    {":", TOKEN_COLON},
    {NULL, -1},
};

bool lexer_read_operator(Lexer *lexer, Token *current_token)
{
    token_literal_to_type_t *matching = NULL;

    for (size_t i = 0; token_operators[i].literal != NULL; i++)
    {
        token_literal_to_type_t *op = &token_operators[i];

        if (op->literal[0] == lexer_current_char(lexer))
        {
            if (op->literal[1] == lexer_peek_char(lexer))
            {
                lexer_next_char(lexer);
                current_token->type = op->type;
                token_append(current_token, lexer_current_char(lexer));

                return true;
            }
            else if (op->literal[1] == '\0')
            {
                matching = op;
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

token_literal_to_type_t token_keywords[] = {
    {"cast", TOKEN_CAST},
    {"constructor", TOKEN_CONSTRUCTOR},
    {"destructor", TOKEN_DESTRUCTOR},
    {"from", TOKEN_FROM},
    {"function", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {"module", TOKEN_MODULE},
    {"return", TOKEN_RETURN},
    {"spec", TOKEN_SPEC},
    {"take", TOKEN_TAKE},
    {"type", TOKEN_TYPE},
    {"use", TOKEN_USE},
    {NULL, -1},
};

bool lexer_read_identifier_or_keyword(Lexer *lexer, Token *current_token)
{
    if (!utils_is_identifier(lexer_current_char(lexer)))
    {
        return false;
    }

    while (utils_is_identifier(lexer_peek_char(lexer)))
    {
        lexer_next_char(lexer);
        token_append(current_token, lexer_current_char(lexer));
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

Token *lexer_next_token(Lexer *lexer)
{
    lexer_eat_white_space(lexer);

    Token *tok = token_create(TOKEN_ILLEGAL, lexer->current_line, lexer->current_column, lexer_current_char(lexer));

    if (!(lexer_read_operator(lexer, tok) ||
          lexer_read_number(lexer, tok) ||
          lexer_read_string(lexer, tok) ||
          lexer_read_identifier_or_keyword(lexer, tok)))
    {
        logger_warn("lexer_next_token got an illegale token: ln%d, col%d \"%s\"", tok->line, tok->column, tok->chr);
    }

    lexer_next_char(lexer);
    //logger_trace("lexer_next_token return ln%d, col%d %s: \"%s\"", tok->line, tok->column, token_as_string(tok), tok->chr);

    return tok;
}