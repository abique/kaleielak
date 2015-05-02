#ifndef TRANSFORM_HH
# define TRANSFORM_HH

# include "node.hh"

class Transform : public Node
{
public:
  MIMOSA_DEF_PTR(Transform);

  inline Transform() : Node() { cairo_matrix_init_identity(&m_); }

  inline virtual void draw(cairo_t *cr) override {
    cairo_save(cr);
    cairo_transform(cr, &m_);
    for (auto it = nodes_.begin(); it != nodes_.end(); ++it)
      it->draw(cr);
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

private:
  mimosa::IntrusiveDList<Node, Node::Ptr, &Node::dl_> nodes_;
  cairo_matrix_t m_;
};

#endif /* !TRANSFORM_HH */
