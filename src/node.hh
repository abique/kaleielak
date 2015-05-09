#ifndef NODE_HH
# define NODE_HH

# include <cmath>

# include <cairo/cairo.h>

# include <mimosa/ref-countable.hh>

# include "value.hh"

class Node : public mimosa::RefCountable<Node>
{
public:
  MIMOSA_DEF_PTR(Node);

  /* Constructor and Destructor */
  inline Node() {}
  inline virtual ~Node() {}

  /* Rendering */
  inline virtual void draw(cairo_t *cr) {
    for (auto it : childs_)
      it->draw(cr);
  }

  inline void addChild(Node::Ptr node) { childs_.push_back(node); }

  std::vector<Node::Ptr> childs_;
};

#endif /* !NODE_HH */
