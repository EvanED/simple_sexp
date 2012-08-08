#include <simple_sexp/sexp.hh>

#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptor/filtered.hpp>

#include "lexer.hh"

#include <iostream>
#include <typeinfo>

using boost::iterator_range;
using boost::make_iterator_range;


bool
is_not_whitespace(std::string const & s)
{
    return (s.size() > 0) && (s[0] != ' ');
}


template <typename ForwardRange>
boost::range_detail::filtered_range<
    bool (*)(const std::basic_string<char>&),
    const boost::iterator_range<boost::token_iterator<basic_regular_expression_matcher<char>,
                                                      std::string::const_iterator,
                                                      std::string>>
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


int main()
{
    std::string s = "(a b (1 \"foo_bar\" 2))";

    auto range = get_tokens(s);
    for(auto token : range) {
        std::cout << token << "\n";
    }
}

