#include "token.c"
#include "lexer.c"
#include "logger.c"

bool test_lexer_expect(source_t *src, token_type_t expected[])
{
    lexer_t *lex = lexer(src);

    bool passed = true;

    for (size_t i = 0; expected[i] != TOKEN_EOF; i++)
    {
        token_t *current_token = lexer_next_token(lex);

        if (current_token->type != expected[i])
        {
            logger_error("test_lexer_expect_from_string failled got %s expected %s!", token_type_as_string(current_token), token_type_string[expected[i]]);
            passed = false;
        }

        token_delete(current_token);
    }

    lexer_delete(lex);

    return passed;
}

void test_lexer_expect_from_string(const char *input, token_type_t expected[])
{
    source_t *src = source_from_string(input, strlen(input));
    bool passed = test_lexer_expect(src, expected);
    source_delete(src);

    if (passed)
    {
        logger_info("test_lexer_expect_from_string '%s' passed!", input);
    }
}

void test_lexer_expect_from_file(const char *file, token_type_t expected[])
{
    source_t *src = source_from_file(file);
    bool passed = test_lexer_expect(src, expected);
    source_delete(src);

    if (passed)
    {
        logger_info("test_lexer_expect_from_file '%s' passed!", file);
    }
}

int main(int argc, char const *argv[])
{
    token_type_t expected_use_system[] = {TOKEN_USE, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_EOF};
    test_lexer_expect_from_file("./tests/use-system.ud", expected_use_system);
    test_lexer_expect_from_string("use System;", expected_use_system);

    token_type_t expected_keywords[] = {TOKEN_USE, TOKEN_MODULE, TOKEN_FUNCTION, TOKEN_EOF};
    test_lexer_expect_from_file("./tests/keywords.ud", expected_keywords);
    test_lexer_expect_from_string("use module function", expected_keywords);

    token_type_t expected_operators[] = {
        TOKEN_EQUAL, TOKEN_NOTEQUAL, TOKEN_ASSIGN, TOKEN_PLUS,
        TOKEN_PLUSPLUS, TOKEN_MINUS, TOKEN_MINUSMINUS, TOKEN_MULT,
        TOKEN_MOD, TOKEN_DIV, TOKEN_DOT, TOKEN_DOTDOT, TOKEN_LPARENT,
        TOKEN_RPARENT, TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_LBRACKET,
        TOKEN_RBRACKET, TOKEN_COMMA, TOKEN_SEMICOLON, TOKEN_EOF};
    test_lexer_expect_from_file("./tests/operators.ud", expected_operators);
    test_lexer_expect_from_string("= != := + ++ - -- * % / . .. ( ) { } [ ] , ; ", expected_operators);

    return 0;
}
