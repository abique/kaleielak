#ifndef NODE_HH
# define NODE_HH

# include <cairo/cairo.h>

# include <mimosa/ref-countable.hh>
# include <mimosa/intrusive-dlist.hh>

class Node : public mimosa::RefCountable<Node>
{
public:
  MIMOSA_DEF_PTR(Node);

  inline virtual ~Node() {}

  inline virtual void draw(cairo_t *cr) {}

  mimosa::IntrusiveDListHook<Node::Ptr> dl_;
  typedef mimosa::IntrusiveDList<Node, Node::Ptr, &Node::dl_> List;
};

#endif /* !NODE_HH */
