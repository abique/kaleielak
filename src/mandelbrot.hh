#ifndef MANDELBROT_HH
# define MANDELBROT_HH

# include <memory>

# include "node.hh"
# include "palette.hh"

/* rename to multibrot */
class Mandelbrot : public Node
{
public:
  Mandelbrot(int w, int h, Value x, Value y, Value scale, Value power,
             Value max_iter = 300, Value cutoff = 12);
  virtual ~Mandelbrot() override;

  virtual void draw(cairo_t *cr) override;

  Pixel color(int iter);

  cairo_surface_t           *surf_;
  const int                  w_; // surface width
  const int                  h_; // surface height
  Pixel                    **rows_;
  Value                      x_;
  Value                      y_;
  Value                      scale_;
  Value                      power_;
  Value                      max_iter_;
  Value                      cutoff_;
  Palette                    palette_;
};

#endif /* !MANDELBROT_HH */
