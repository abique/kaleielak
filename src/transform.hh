#ifndef TRANSFORM_HH
# define TRANSFORM_HH

# include "node.hh"

class Transform : public Node
{
public:
  inline Transform() : Node() { cairo_matrix_init_identity(&m_); }

  inline ~Transform() {}

  inline virtual void draw(cairo_t *cr) override {
    cairo_save(cr);
    cairo_transform(cr, &m_);
    Node::draw(cr);
    cairo_restore(cr);
  }

  inline void rotate(double radians) {
    cairo_matrix_rotate(&m_, radians);
  }

  inline void translate(double tx, double ty) {
    cairo_matrix_translate(&m_, tx, ty);
  }

  inline void scale(double sx, double sy) {
    cairo_matrix_scale(&m_, sx, sy);
  }

protected:
  cairo_matrix_t m_;
};

#endif /* !TRANSFORM_HH */
