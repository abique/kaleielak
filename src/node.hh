#ifndef NODE_HH
# define NODE_HH

# include <cmath>

# include <cairo/cairo.h>

# include <mimosa/intrusive-dlist.hh>

# include "value.hh"

class Node
{
public:
  /* Constructor and Destructor */
  inline Node() {}
  inline virtual ~Node() {
    while (!childs_.empty()) {
      auto node = childs_.front();
      childs_.popFront();
      delete node;
    }
  }

  /* Rendering */
  inline virtual void draw(cairo_t *cr) {
    for (auto it = childs_.begin(); it != childs_.end(); ++it)
    it->draw(cr);
  }

  inline void addChild(Node *node) { childs_.pushBack(node); }

  /* Tree structure */
  mimosa::IntrusiveDListHook<Node *> dl_;
  mimosa::IntrusiveDList<Node, Node *, &Node::dl_> childs_;
};

#endif /* !NODE_HH */
