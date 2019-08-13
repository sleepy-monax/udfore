#include "token.c"
#include "lexer.c"
#include "logger.c"

void test_lexer_expect(const char *input, token_type_t expected[])
{
    source_t *src = source_from_string(input, strlen(input));
    lexer_t *lex = lexer(src);

    for (size_t i = 0; expected[i] != TOKEN_EOF; i++)
    {
        token_t *current_token = lexer_next_token(lex);

        if (current_token->type != expected[i])
        {
            logger_error("lexer test failled got %s expected %s!", token_type_as_string(current_token), token_type_string[expected[i]]);
        }

        token_delete(current_token);
    }
}

int main(int argc, char const *argv[])
{
    test_lexer_expect("use System;", (token_type_t[]){TOKEN_USE, TOKEN_IDENTIFIER, TOKEN_SEMICOLON});
    return 0;
}
