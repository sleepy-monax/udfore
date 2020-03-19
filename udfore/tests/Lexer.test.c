#include <string.h>

#include "udfore/lexer/Lexer.h"
#include "udfore/source/Source.h"
#include "udfore/token/Token.h"
#include "udfore/utils/Logger.h"

bool test_lexer_expect(Source *src, const TokenType expected[])
{
    Lexer *lex = lexer_create(src);

    bool passed = true;

    for (size_t i = 0; expected[i] != TOKEN_EOF; i++)
    {
        Token *current_token = lexer_next_token(lex);

        if (current_token->type != expected[i])
        {
            logger_error("test_lexer_expect failled got %s expected %s!", token_as_string(current_token), token_type_as_string(expected[i]));
            passed = false;
        }

        token_destroy(current_token);
    }

    if (!lexer_is_EOF(lex))
    {
        logger_error("Didn't reached EOF!");
        passed = false;
    }

    lexer_destroy(lex);

    return passed;
}

void test_lexer_expect_from_string(const char *input, const TokenType expected[])
{
    Source *src = string_source_create(input, strlen(input));
    bool passed = test_lexer_expect(src, expected);
    source_destroy(src);

    if (passed)
    {
        logger_info("test_lexer_expect_from_string '%s' passed!", input);
    }
    else
    {
        logger_error("test_lexer_expect_from_string '%s' failled!", input);
    }
}

void test_lexer_expect_from_file(const char *file, const TokenType expected[])
{
    Source *src = file_source_create(file);
    bool passed = test_lexer_expect(src, expected);
    source_destroy(src);

    if (passed)
    {
        logger_info("test_lexer_expect_from_file '%s' passed!", file);
    }
    else
    {
        logger_error("test_lexer_expect_from_file '%s' failled!", file);
    }
}

int main(int argc, char const *argv[])
{
    (void)argc, (void)argv;

    const TokenType expected_empty[] = {TOKEN_EOF};
    test_lexer_expect_from_file("./tests/empty.ud", expected_empty);
    test_lexer_expect_from_string("", expected_empty);

    const TokenType expected_use_system[] = {TOKEN_USE, TOKEN_IDENTIFIER, TOKEN_SEMICOLON, TOKEN_EOF};
    test_lexer_expect_from_file("./tests/use-system.ud", expected_use_system);
    test_lexer_expect_from_string("use System;", expected_use_system);

    const TokenType expected_keywords[] = {
        TOKEN_CAST,
        TOKEN_CONSTRUCTOR,
        TOKEN_DESTRUCTOR,
        TOKEN_FROM,
        TOKEN_FUNCTION,
        TOKEN_LET,
        TOKEN_MODULE,
        TOKEN_RETURN,
        TOKEN_SPEC,
        TOKEN_TAKE,
        TOKEN_TYPE,
        TOKEN_USE,
        TOKEN_EOF,
    };
    test_lexer_expect_from_file("./tests/keywords.ud", expected_keywords);
    test_lexer_expect_from_string("cast constructor destructor from function let module return spec take type use", expected_keywords);

    const TokenType expected_operators[] = {
        TOKEN_EQUAL,
        TOKEN_NOTEQUAL,
        TOKEN_BIGGER_THAN,
        TOKEN_LESS_THAN,
        TOKEN_ASSIGN,
        TOKEN_PLUS,
        TOKEN_PLUSPLUS,
        TOKEN_MINUS,
        TOKEN_MINUSMINUS,
        TOKEN_MULT,
        TOKEN_MOD,
        TOKEN_DIV,
        TOKEN_DOT,
        TOKEN_DOTDOT,
        TOKEN_ARROW,
        TOKEN_LPARENT,
        TOKEN_RPARENT,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_COMMA,
        TOKEN_SEMICOLON,
        TOKEN_QUESTION,
        TOKEN_COLON,
        TOKEN_EOF,
    };

    test_lexer_expect_from_file("./tests/operators.ud", expected_operators);
    test_lexer_expect_from_string("= != > < := + ++ - -- * % / . .. -> ( ) { } [ ] , ; ? :", expected_operators);

    const TokenType expected_identifier[] = {
        TOKEN_IDENTIFIER,
        TOKEN_IDENTIFIER,
        TOKEN_IDENTIFIER,
        TOKEN_IDENTIFIER,
        TOKEN_NUMBER,
        TOKEN_EOF,
    };

    test_lexer_expect_from_string("_abc123 _abc abc_ a_bc 1234", expected_identifier);

    return 0;
}
