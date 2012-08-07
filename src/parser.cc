#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

namespace Tokens {
    enum Token {
        L_Paren,
        R_Paren,
        String_Literal,
        Integer_Literal,
        Symbol
    };
}

template <typename Lexer>
struct word_count_tokens : lex::lexer<Lexer>
{
    word_count_tokens()
    {
        this->self.add
            ("(", L_Paren)
            (")", R_Paren)
            ("\"...\"", String_Literal)
            ("[a-zA-Z]+", Symbol)
            ;
    }
};
