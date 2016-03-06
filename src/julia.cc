#include <cassert>
#include <complex>
#include <iostream>

#include "julia.hh"

Julia::Julia(int w, int h)
  : w_(w),
    h_(h),
    surf_(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h)),
    rows_((Pixel **)malloc(sizeof (*rows_) * h)),
    iters_((uint32_t *)malloc(sizeof (*iters_) * w * h)),
    norms_((double *)malloc(sizeof (*norms_) * w * h)),
    x_(0),
    y_(0),
    scale_(1),
    iter_limit_(10000),
    cutoff_(1),
    rpoly_([] (std::complex<float_type> z) { return z; })
{
  assert(surf_);
  assert(rows_);
  assert(iters_);
  assert(norms_);

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
  free(iters_);
}

void
Julia::draw(cairo_t *cr) {

  cairo_surface_flush(surf_);

  std::cout << "scale: " << scale_ << std::endl;

  /* fill our image buffer */
  const long double x0 = x_ - scale_;     // start
  const long double xr = 2 * scale_ / (double)w_; // ramp

  const long double y0 = y_ - scale_;     // start
  const long double yr = 2 * scale_ / (double)h_; // ramp

  uint32_t min_iter = iter_limit_;
  uint32_t max_iter = 1;
  const long double cutoff = cutoff_;

#pragma omp parallel for
  for (int x = 0; x < w_; ++x) {
#pragma omp parallel for
    for (int y = 0; y < h_; ++y) {

      // super sampling 5x
      std::array<std::pair<uint32_t, float_type>, 25> super_iters;
      for (int m = 0; m < 5; ++m) {
        for (int n = 0; n < 5; ++n) {
          std::complex<float_type> z(x0 + (x + m / 5.0) * xr, y0 + (y + n / 5.0) * yr);

          uint32_t i;
          for (i = 0; i < iter_limit_ && std::norm(z) <= cutoff; ++i)
            z = rpoly_(z);
          super_iters[m + 5 * n] = std::make_pair(i, std::norm(z));
        }
      }
      std::sort(super_iters.begin(), super_iters.end());

      uint32_t i = super_iters[12].first;
      if (min_iter > i)
        min_iter = i;
      if (max_iter < i)
        max_iter = i;

      iters_[y * w_ + x] = i;
      norms_[y * w_ + x] = super_iters[12].second;
    }
  }

  const long double log_div = std::log((long double)(max_iter + 1) / (long double)min_iter);
#pragma omp parallel for
  for (int x = 0; x < w_; ++x) {
#pragma omp parallel for
    for (int y = 0; y < h_; ++y) {
      uint32_t i = iters_[y * w_ + x];
      long double norm = norms_[y * w_ + x];

      rows_[y][x] = palette_.gradient(std::log((long double)(i + std::exp(-(norm / cutoff - 1))) / (long double)min_iter) /
                                      log_div);
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
