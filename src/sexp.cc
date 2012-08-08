#include <simple_sexp/sexp.hh>

namespace simple_sexp
{
    void
    LeafExp::accept(SExpVisitor & visitor) const
    {
        visitor.previsit_leaf(*this);
        visitor.postvisit_leaf(*this);
    }

    void
    ListExp::accept(SExpVisitor & visitor) const
    {
        visitor.previsit_list(*this);
        for (auto child: this->children_) {
            child->accept(visitor);
        }
        visitor.postvisit_list(*this);
    }
}


// Yo emacs!
// Local Variables:
//     c-file-style: "ellemtel"
//     c-basic-offset: 4
//     indent-tabs-mode: nil
// End:
