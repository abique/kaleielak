#include <cassert>
#include <complex>

#include "julia.hh"

Julia::Julia(int w, int h)
  : w_(w),
    h_(h),
    surf_(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h)),
    rows_((Pixel **)malloc(sizeof (*rows_) * h)),
    x_(0),
    y_(0),
    scale_(1),
    max_iter_(100),
    cutoff_(1),
    rpoly_([] (std::complex<double> z) { return z; })
{
  assert(surf_);
  assert(rows_);

  const int stride = cairo_image_surface_get_stride(surf_);
  unsigned char *data = cairo_image_surface_get_data(surf_);
  for (int y = 0; y < h_; ++y) {
    rows_[y] = (Pixel *)(stride * y + data);
  }
}

Julia::~Julia()
{
  cairo_surface_destroy(surf_);
  free(rows_);
}

void
Julia::draw(cairo_t *cr) {

  cairo_surface_flush(surf_);

  /* fill our image buffer */
  const double x0 = x_ - scale_;     // start
  const double xr = 2 * scale_ / (double)w_; // ramp

  const double y0 = y_ - scale_;     // start
  const double yr = 2 * scale_ / (double)h_; // ramp

#pragma omp parallel for
  for (int x = 0; x < w_; ++x) {
#pragma omp parallel for
    for (int y = 0; y < h_; ++y) {
      std::complex<double> z(x0 + x * xr, y0 + y * yr);

      int i;
      const double cutoff = cutoff_;
      for (i = 0; i < max_iter_ && std::norm(z) <= cutoff; ++i)
        z = rpoly_(z);

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

  cairo_surface_mark_dirty(surf_);

  cairo_save(cr);
  cairo_scale(cr, 1.0 / w_, 1.0 / h_);
  cairo_translate(cr, -w_ / 2.0, -h_ / 2.0);
  cairo_set_source_surface(cr, surf_, 0, 0);
  cairo_paint(cr);
  cairo_restore(cr);
}

Pixel
Julia::color(int iter)
{
  return palette_.color(iter);
}
