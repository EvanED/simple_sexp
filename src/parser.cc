#include <simple_sexp/sexp.hh>

#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "lexer.hh"

#include <iostream>
#include <typeinfo>

using boost::iterator_range;
using boost::make_iterator_range;
using std::string;
using namespace simple_sexp;

bool
is_not_whitespace(string const & s)
{
    return (s.size() > 0) && (s[0] != ' ');
}


template <typename ForwardRange>
boost::range_detail::filtered_range<
    bool (*)(const std::basic_string<char>&),
    const boost::iterator_range<
        boost::token_iterator<basic_regular_expression_matcher<char>,
                              string::const_iterator,
                              string>>
    >
get_tokens(ForwardRange const & input)
{
    typedef boost::tokenizer<basic_regular_expression_matcher<char> > tokenizer;

    basic_regular_expression_matcher<char> matcher;
    try {
        matcher.add_regex("\\(");
        matcher.add_regex("\\)");
        matcher.add_regex("[a-zA-Z]+");
        matcher.add_regex("[0-9]+");
        matcher.add_regex("\"[^\"\\\\]*\"");
        matcher.add_regex(" +");
    }
    catch (std::exception & e) {
        std::cout << "Internal error 398928: exception: " << e.what() << "\n";
        throw;
    }
    
    tokenizer tok(std::begin(input), std::end(input), matcher);

    return
        make_iterator_range(tok.begin(), tok.end())
        | boost::adaptors::filtered(is_not_whitespace);
}



template <typename ForwardIterator>
SExp::Ptr
parse_sexp(ForwardIterator & next, ForwardIterator end)
{
    assert(next != end);
    string lexeme = *next;
    assert(lexeme.size() > 0);
    ++next;
    
    if (lexeme == "(") {
        std::vector<SExp::Ptr> children;
        while (*next != ")") {
            children.push_back(parse_sexp(next, end));
        }
        // Forward over ")"
        ++next;
        return SExp::Ptr(new ListExp(children));
    }

    if (std::isdigit(lexeme[0])) {
        return SExp::Ptr(new IntExp(lexeme));
    }

    if (lexeme[0] == '\"') {
        return SExp::Ptr(new StringExp(lexeme));
    }

    assert(lexeme[0] != '(' && lexeme[0] != ')');

    return SExp::Ptr(new SymbolExp(lexeme)); 
}


class Printer : public SExpVisitor
{
public:
    virtual void previsit_leaf(LeafExp const & leaf) {
        std::cout << leaf.value() << " ";
    }
    
    virtual void previsit_list(ListExp const & list) {
        std::cout << "( ";
    }
    
    virtual void postvisit_list(ListExp const & list) {
        std:: cout << ") ";
    }
};



int main()
{
    string s = "(a b (1 \"foo_bar\" 2))";

    auto range = get_tokens(s);
    auto next = range.begin();
    auto sexp = parse_sexp(next, range.end());

    sexp->accept(Printer());
    std::cout << "\n";
}

