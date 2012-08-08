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
        typedef std::shared_ptr<SExp const> Ptr;

        ///
        /// Traverse this tree with the given visitor
        virtual
        void
        accept(SExpVisitor & visitor) const = 0;
        
        void
        accept(SExpVisitor && visitor) const {
            accept(static_cast<SExpVisitor&>(visitor));
        }

        virtual ~SExp() {}
    };


    /// This class represents any leaf. This may be strings, numbers, etc.,
    /// and the contents are from the input exactly. They will include the
    /// surrounding quotes, escape sequences, etc.
    class LeafExp : public SExp
    {
        std::string const str_;
        
    public:
        typedef std::shared_ptr<LeafExp const> Ptr;
        
        LeafExp(std::string const & str)
            : str_(str)
        {}

        std::string
        value() const { return str_; }

        virtual
        void
        accept(SExpVisitor & visitor) const CPP11_OVERRIDE;
    };

    class StringExp : public LeafExp
    {
    public:
        typedef std::shared_ptr<StringExp const> Ptr;
        
        StringExp(std::string const & str)
            : LeafExp(str)
        {}
    };

    class SymbolExp : public LeafExp
    {
    public:
        typedef std::shared_ptr<SymbolExp const> Ptr;
        
        SymbolExp(std::string const & str)
            : LeafExp(str)
        {}
    };

    class IntExp : public LeafExp
    {
    public:
        typedef std::shared_ptr<IntExp const> Ptr;
        
        IntExp(std::string const & str)
            : LeafExp(str)
        {}
    };
       


    ///
    /// This represents a list.
    class ListExp : public SExp
    {
        std::vector<SExp::Ptr> children_;
        
    public:
        typedef std::shared_ptr<ListExp const> Ptr;
        
        ListExp(std::vector<SExp::Ptr> const & children)
            : children_(children)
        {}

        std::vector<SExp::Ptr> const &
        children() const {
            return children_;
        }

        virtual
        void
        accept(SExpVisitor & visitor) const CPP11_OVERRIDE;
    };

    class SExpVisitor
    {
    public:
        virtual void previsit_leaf(LeafExp const & leaf) { (void) leaf; }
        virtual void previsit_list(ListExp const & list) { (void) list; }

        virtual void postvisit_leaf(LeafExp const & leaf) { (void) leaf; }
        virtual void postvisit_list(ListExp const & list) { (void) list; }

        virtual ~SExpVisitor() {}
    };


    extern
    SExp::Ptr
    parse_from_string(std::string const & str);
}


// Yo emacs!
// Local Variables:
//     c-file-style: "ellemtel"
//     c-basic-offset: 4
//     indent-tabs-mode: nil
// End:

#endif /* SIMPLE_SEXP_SEXP_HH */
