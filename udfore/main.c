#include "udfore/lexer/Lexer.h"
#include "udfore/source/Source.h"
#include "udfore/utils/Logger.h"

int main(int argc, char const *argv[])
{
    logger_set_level(LOGGER_TRACE);

    if (argc > 1)
    {
        Source *src = file_source_create(argv[1]);
        Lexer *lex = lexer_create(src);

        while (!lexer_is_EOF(lex))
        {
            Token *tok = lexer_next_token(lex);

            token_destroy(tok);
        }

        lexer_destroy(lex);
        source_destroy(src);
    }

    return 0;
}
