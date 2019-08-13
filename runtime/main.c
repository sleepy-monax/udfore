#include "source.c"
#include "lexer.c"

int main(int argc, char const *argv[])
{

    logger_set_quiet(0);
    logger_set_level(LOGGER_TRACE);

    if (argc > 1)
    {
        source_t *src = source_from_file(argv[1]);
        lexer_t *lex = lexer(src);

        while (!lexer_is_EOF(lex))
        {
            token_t *tok = lexer_next_token(lex);

            token_delete(tok);
        }
    }

    return 0;
}
