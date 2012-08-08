#include <vector>
//#include <regex>
#include <boost/regex.hpp>


template <typename Char,
          typename RegexType = boost::basic_regex<Char>
          >
class basic_regular_expression_matcher
{
public:
    typedef RegexType regex_type;
    
    basic_regular_expression_matcher()
    {}
    
    void
    add_regex(regex_type const & regex)
    {
        regexes_.push_back(regex);
    }

    template <typename St, typename Sa>
    void
    add_regex(std::basic_string<Char, St, Sa> const & regex_string)
    {
        regexes_.push_back(regex_type(regex_string,
                                      boost::regex_constants::ECMAScript
                                      | boost::regex_constants::optimize));
    }

    void
    add_regex(std::basic_string<Char> const & regex_string)
    {
        regexes_.push_back(regex_type(regex_string,
                                      boost::regex_constants::ECMAScript
                                      | boost::regex_constants::optimize));
    }

    template <typename InputIterator, typename Token>
    bool operator() (InputIterator & next, InputIterator end, Token & tok)
    {
        InputIterator start(next);

        //std::cout << "=== basic_regular_expression_matcher: operator()\n";

        if (next == end) {
            return false;
        }

        // Check which regex matches a longer prefix
        typedef boost::match_results<InputIterator> Match;
        typedef typename std::vector<regex_type>::const_iterator RegexIterator;

        typename Match::difference_type longest_length = 0;
        RegexIterator longest_regex = regexes_.end();

        for (RegexIterator current_regex = regexes_.begin();
             current_regex != regexes_.end(); ++current_regex)
        {
            Match match;
            bool matched = boost::regex_search(start, end, match, *current_regex,
                                             boost::regex_constants::match_continuous);

            //std::cout << "===    testing regex; " << (matched ? "match" : "no match") << "\n";
            
            if (matched && match.length() > longest_length) {
                longest_regex = current_regex;
                longest_length = match.length();
            }
        }

        if (longest_regex == regexes_.end()) {
            return false;
        }

        std::advance(next, longest_length);
        tok.assign(start, next);

        return true;
    }

    void reset() {}

private:
    std::vector<regex_type> regexes_;
};
