#ifndef COLOR_HH
# define COLOR_HH

# include "node.hh"

class Color : public Node
{
public:
  inline Color(Value red, Value green, Value blue, Value alpha = 1.0)
    : Node(), r_(red), g_(green), b_(blue), a_(alpha)
  {
  }

  inline virtual void draw(cairo_t *cr) override {
    cairo_save(cr);
    cairo_set_source_rgba(cr, r_, g_, b_, a_);
    Node::draw(cr);
    cairo_restore(cr);
  }

  Value r_;
  Value g_;
  Value b_;
  Value a_;
};

#endif /* !COLOR_HH */
