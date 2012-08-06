#include <simple_sexp/sexp.hh>

namespace simple_sexp
{
    void
    LeafExp::accept(SExpVisitor & visitor) const
    {
        visitor.postvisit_leaf(*this, this->str_);
    }

    void
    ListExp::accept(SExpVisitor & visitor) const
    {
        for (auto child: this->children_) {
            child->accept(visitor);
        }
        visitor.postvisit_list(*this, this->children_);
    }
}


// Yo emacs!
// Local Variables:
//     c-file-style: "ellemtel"
//     c-basic-offset: 4
//     indent-tabs-mode: nil
// End:
