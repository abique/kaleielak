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

  typedef std::function<
    std::complex<double> (std::complex<double>)> fct_type;

  cairo_surface_t  *surf_;
  const int         w_;         // surface width
  const int         h_;         // surface height
  Pixel           **rows_;
  Value             x_;
  Value             y_;
  Value             scale_;
  Value             max_iter_;
  Value             cutoff_;
  Palette           palette_;
  fct_type          rpoly_;
};

#endif /* !JULIA_HH */
