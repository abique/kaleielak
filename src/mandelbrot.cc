#include <cassert>
#include <complex>

#include "mandelbrot.hh"

Mandelbrot::Mandelbrot(int w, int h, Value x, Value y,
                       Value scale, Value power, Value max_iter)
  : w_(w),
    h_(h),
    surf_(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h)),
    rows_((Pixel **)malloc(sizeof (*rows_) * h)),
    x_(x),
    y_(y),
    scale_(scale),
    power_(power),
    max_iter_(max_iter)
{
  assert(surf_);
  assert(rows_);

  const int stride = cairo_image_surface_get_stride(surf_);
  unsigned char *data = cairo_image_surface_get_data(surf_);
  for (int y = 0; y < h_; ++y) {
    rows_[y] = (Pixel *)(stride * y + data);
  }
}

Mandelbrot::~Mandelbrot()
{
  cairo_surface_destroy(surf_);
  free(rows_);
}

void
Mandelbrot::draw(cairo_t *cr) {
  /* fill our image buffer */
  const double x0 = x_ - scale_;     // start
  const double xr = 2 * scale_ / (double)w_; // ramp

  const double y0 = y_ - scale_;     // start
  const double yr = 2 * scale_ / (double)h_; // ramp

#pragma omp parallel for
  for (int x = 0; x < w_; ++x) {
    for (int y = 0; y < h_; ++y) {
      const std::complex<double> c(x0 + x * xr, y0 + y * yr);
      std::complex<double> z(0, 0);

      int i;
      for (i = 0; i < max_iter_ && std::norm(z) < 1; ++i)
        z = std::pow(z, power_) + c;

      if (i == 0) {
        rows_[y][x] = color(i);
      } else {
        double a = std::exp(-(std::norm(z) - 1));
        double b = 1 - a;
        Pixel p0 = color(i);
        Pixel p1 = color(i - 1);
        rows_[y][x] = Pixel(p0.r * a + p1.r * b,
                            p0.g * a + p1.g * b,
                            p0.b * a + p1.b * b);
      }
    }
  }

  cairo_surface_write_to_png(surf_, "mandle.png");

  cairo_save(cr);
  cairo_set_source_surface(cr, surf_, 0, 0);
  cairo_paint(cr);
  cairo_restore(cr);
}

Pixel
Mandelbrot::color(int iter)
{
  return palette_.color(iter);
}
