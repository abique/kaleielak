#ifndef ARC_HH
# define ARC_HH

# include "node.hh"

class Arc : public Node
{
public:
  inline Arc(Value x, Value y, Value radius, Value angle1, Value angle2)
    : x_(x), y_(y), radius_(radius), angle1_(angle1), angle2_(angle2)
  {
  }

  inline virtual void draw(cairo_t *cr) override {
    cairo_new_path(cr);
    cairo_arc(cr, x_, y_, radius_, angle1_, angle2_);
    cairo_stroke(cr);
  }

  Value x_;
  Value y_;
  Value radius_;
  Value angle1_;
  Value angle2_;
};

#endif /* !ARC_HH */
