#ifndef CIRCLE_HH
# define CIRCLE_HH

# include "node.hh"

class Circle : public Node
{
public:
  inline Circle(double x, double y, Value radius)
    : Node(), x_(x), y_(y), radius_(radius)
  {
  }

  inline virtual void draw(cairo_t *cr) override {
    cairo_new_path(cr);
    cairo_arc(cr, x_, y_, radius_, 0, 2 * M_PI);
    cairo_stroke(cr);
  }

  double x_;
  double y_;
  Value radius_;
};

#endif /* !CIRCLE_HH */
