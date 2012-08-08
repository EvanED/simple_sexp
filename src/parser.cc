#include <simple_sexp/sexp.hh>

#include <boost/tokenizer.hpp>

#include "lexer.hh"

#include <iostream>

int main()
{
    std::string s = "a b (1 2))";
    
    typedef boost::tokenizer<basic_regular_expression_matcher<char> > tokenizer;

    basic_regular_expression_matcher<char> matcher;
    try {
        matcher.add_regex("a");
        matcher.add_regex("\\)");
    }
    catch (std::exception & e) {
        std::cout << "Exception: " << e.what() << "\n";
        throw;
    }
    
    tokenizer tok(s.begin(), s.end(), matcher);
    
    for(tokenizer::iterator beg=tok.begin(); beg!=tok.end();++beg){
        std::cout << *beg << "\n";
    }
}

