#ifndef RECTANGLE_HH
# define RECTANGLE_HH

# include "node.hh"

class Rectangle : public Node
{
public:
  inline Rectangle(Value x, Value y, Value w, Value h)
    : Node(), x_(x), y_(y), w_(w), h_(h)
  {
  }

  inline virtual void draw(cairo_t *cr) override {
    cairo_new_path(cr);
    cairo_rectangle(cr, x_, y_, w_, h_);
    cairo_stroke(cr);
  }

  Value x_;
  Value y_;
  Value w_;
  Value h_;
};

#endif /* !RECTANGLE_HH */
