#ifndef JULIA_HH
# define JULIA_HH

# include <memory>
# include <complex>
# include <functional>

# include "node.hh"
# include "palette.hh"

class Julia : public Node
{
public:
  Julia(int w, int h);
  virtual ~Julia() override;

  virtual void draw(cairo_t *cr) override;

  Pixel color(int iter);

  typedef double float_type;
  typedef std::function<
    std::complex<float_type> (std::complex<float_type>)> fct_type;

  cairo_surface_t  *surf_;
  const int         w_;         // surface width
  const int         h_;         // surface height
  Pixel           **rows_;
  uint32_t         *iters_;
  double           *norms_;
  Value             x_;
  Value             y_;
  Value             scale_;
  Value             iter_limit_;
  Value             cutoff_;
  Palette           palette_;
  fct_type          rpoly_;

  float_type        max_iter_;
  float_type        min_iter_;
};

#endif /* !JULIA_HH */
