#include "udfore/parser/Parser.h"

ASTProgram *parser_parse_program(Parser *parser)
{
    ASTProgram *program = astprogram_create();

    while (!parser_current_is(parser, TOKEN_EOF))
    {
        ASTStatement *statement = parser_parse_statement(parser);

        if (statement)
        {
            astprogram_append_statement(program, statement);
        }

        parser_advance(parser); // skip rbrace
    }

    return program;
}