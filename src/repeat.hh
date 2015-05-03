#ifndef REPEAT_HH
# define REPEAT_HH

# include "transform.hh"

class RepeatedTransform : public Transform
{
public:
  inline RepeatedTransform(uint32_t count)
    : Transform(),
      count_(count)
  {
  }

  inline void draw(cairo_t *cr) {
    cairo_save(cr);
    for (i_ = 0; i_ < count_; ++i_) {
      cairo_transform(cr, &m_);
      Node::draw(cr);
    }
    cairo_restore(cr);
  }

  uint32_t i_;
  uint32_t count_;
};

#endif /* !REPEAT_HH */
