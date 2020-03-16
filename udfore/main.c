#include "udfore/lexer/Lexer.h"
#include "udfore/parser/Parser.h"
#include "udfore/source/Source.h"
#include "udfore/utils/Logger.h"

int main(int argc, char const *argv[])
{
    logger_set_level(LOGGER_TRACE);

    if (argc > 1)
    {
        Source *source = file_source_create(argv[1]);
        Lexer *lexer = lexer_create(source);
        Parser *parser = parser_create(lexer);

        ASTProgram *program = parser_parse_program(parser);

        parser_destroy(parser);
        lexer_destroy(lexer);
        source_destroy(source);

        char *output = astnode_serialize(ASTNODE(program));

        printf("%s", output);

        free(output);
        astnode_destroy(ASTNODE(program));
    }

    return 0;
}
