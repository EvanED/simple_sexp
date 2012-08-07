#include <simple_sexp/sexp.hh>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

namespace lex = boost::spirit::lex;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

using simple_sexp::SExp;
using ascii::space_type;
using std::vector;


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
struct tokens : lex::lexer<Lexer>
{
    tokens()
    {
        this->self.add
            ("(", Tokens::L_Paren)
            (")", Tokens::R_Paren)
            ("\"...\"", Tokens::String_Literal)
	    ("[0-9]+", Tokens::Integer_Literal)
            ("[a-zA-Z]+", Tokens::Symbol)
            ;
    }
};

template <typename Iterator>
struct sexp_grammar
    : qi::grammar<Iterator, SExp::Ptr, space_type>
{
    qi::rule<Iterator, SExp::Ptr, space_type> sexp;
    qi::rule<Iterator, vector<SExp::Ptr>, space_type> sexp_list;

    sexp_grammar()
    {
	using qi::token;
	using namespace Tokens;

	sexp_list %= *sexp;

	sexp = token(String_Literal)
	    |  token(Integer_Literal)
	    |  token(Symbol)
	    | (token(L_Paren)
	       >> sexp_list
	       >> token(R_Paren)
	       );
    }
};
