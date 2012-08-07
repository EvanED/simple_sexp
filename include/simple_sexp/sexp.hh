#ifndef SIMPLE_SEXP_SEXP_HH
#define SIMPLE_SEXP_SEXP_HH

#include <vector>
#include <memory>
#include <string>

// Needs GCC 4.7
#define CPP11_OVERRIDE

namespace simple_sexp
{
    class SExpVisitor;
    
    ///
    /// Base class for all s-expressions.
    class SExp : public std::enable_shared_from_this<SExp>
    {
    public:
        /// The following is a reference-counted smart pointer to SExp. It is
        /// currently a std::shared_ptr, but this is not guaranteed to remain
        /// true in the future. However, it probably will.
        typedef std::shared_ptr<SExp> Ptr;

        ///
        /// Traverse this tree with the given visitor
        virtual
        void
        accept(SExpVisitor & visitor) const = 0;
        
        virtual ~SExp() {}
    };


    /// This class represents any leaf. This may be strings, numbers, etc.,
    /// and the contents are from the input exactly. They will include the
    /// surrounding quotes, escape sequences, etc.
    class LeafExp : public SExp
    {
        std::string const str_;
        
    public:
        LeafExp(std::string const & str)
            : str_(str)
        {}

        virtual
        void
        accept(SExpVisitor & visitor) const CPP11_OVERRIDE;
    };


    ///
    /// This represents a list.
    class ListExp : public SExp
    {
        std::vector<SExp::Ptr> children_;
        
    public:
        ListExp(std::vector<SExp::Ptr> const & children)
            : children_(children)
        {}

        virtual
        void
        accept(SExpVisitor & visitor) const CPP11_OVERRIDE;
    };


    class SExpVisitor
    {
    public:
        virtual void postvisit_leaf(LeafExp const & leaf, std::string const & str) = 0;
        virtual void postvisit_list(ListExp const & list, std::vector<SExp::Ptr> const & children) = 0;

        virtual ~SExpVisitor() {}
    };
}


// Yo emacs!
// Local Variables:
//     c-file-style: "ellemtel"
//     c-basic-offset: 4
//     indent-tabs-mode: nil
// End:

#endif /* SIMPLE_SEXP_SEXP_HH */
