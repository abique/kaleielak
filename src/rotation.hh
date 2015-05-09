#ifndef ROTATION_HH
# define ROTATION_HH

# include "node.hh"

class Rotation : public Node
{
public:
  inline Rotation(Value angle) : Node(), angle_(angle) {}

  inline virtual void draw(cairo_t *cr) override {
    cairo_save(cr);
    cairo_matrix_t m_;
    cairo_matrix_init_rotate(&m_, angle_);
    cairo_transform(cr, &m_);
    Node::draw(cr);
    cairo_restore(cr);
  }

  Value angle_;
};

#endif /* !ROTATION_HH */
